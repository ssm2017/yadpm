<?php

/**
 * Admin panel
 */
function yadpm_admin_form($form, &$form_state) {

  $form = array();

  $form['log'] = array(
    '#type'         => 'fieldset',
    '#title'        => 'Log',
    '#collapsible'  => FALSE,
    '#collapsed'    => FALSE,
  );
  $form['log']['yadpm_logfilepath'] = array(
    '#type'           => 'textfield',
    '#title'          => 'Logfilepath',
    '#default_value'  => variable_get('yadpm_logfilepath', '/var/www'),
    '#description'    => t("Path to store the log file. Default is : !yadpm_logfilepath", array('!yadpm_logfilepath'=> '/var/www')),
  );
  $form['api'] = array(
    '#type'         => 'fieldset',
    '#title'        => 'API',
    '#collapsible'  => FALSE,
    '#collapsed'    => FALSE,
  );
  /*$form['api']['yadpm_endpoint_url'] = array(
    '#type'           => 'textfield',
    '#title'          => 'Endpoint URL',
    '#default_value'  => variable_get('yadpm_endpoint_url','https://svcs.sandbox.paypal.com/AdaptivePayments/Pay'),
    '#description'    => "URL de destination de l' api. Par defaut : https://svcs.sandbox.paypal.com/AdaptivePayments/Pay",
  );*/
  $form['api']['yadpm_use_sandbox'] = array(
    '#type'           => 'checkbox',
    '#title'          => 'Sandbox',
    '#default_value'  => variable_get('yadpm_use_sandbox',1),
    '#description'    => t('Use the paypal sandbox.'),
  );
  /*$form['api']['yadpm_username'] = array(
    '#type'           => 'textfield',
    '#title'          => 'Username',
    '#default_value'  => variable_get('yadpm_username',''),
    '#description'    => "Nom d'utilisateur de l'api paypal.",
  );
  $form['api']['yadpm_password'] = array(
    '#type'           => 'textfield',
    '#title'          => 'Password',
    '#default_value'  => variable_get('yadpm_password',''),
    '#description'    => "Mot de passe de l'api paypal.",
  );
  $form['api']['yadpm_signature'] = array(
    '#type'           => 'textfield',
    '#title'          => 'Signature',
    '#default_value'  => variable_get('yadpm_signature',''),
    '#description'    => "Signature de l'api paypal.",
  );*/
  $form['api']['yadpm_receiver'] = array(
    '#type'           => 'textfield',
    '#title'          => 'Receiver',
    '#default_value'  => variable_get('yadpm_receiver','bbbb_1348008756_biz@gmail.com'),
    '#description'    => t("Paypal account that receive the money."),
  );
  /*$form['api']['yadpm_ipnNotificationUrl'] = array(
    '#type'           => 'textfield',
    '#title'          => 'ipnNotificationUrl',
    '#default_value'  => variable_get('yadpm_ipnNotificationUrl',$GLOBALS['base_url']. '/fg/paypal/ipnnotification'),
    '#description'    => "ipnNotificationUrl de l'api paypal.",
  );*/

  $form['ssl'] = array(
    '#type'         => 'fieldset',
    '#title'        => 'SSL',
    '#collapsible'  => FALSE,
    '#collapsed'    => FALSE,
  );
  $form['ssl']['yadpm_my_key_file_path'] = array(
    '#type'           => 'textfield',
    '#title'          => 'Private key',
    '#default_value'  => variable_get('yadpm_my_key_file_path','/etc/apache2/openssl/paypal_key.pem'),
    '#description'    => t('Path to your own private ssl key'),
  );
  $form['ssl']['yadpm_my_cert_file_path'] = array(
    '#type'           => 'textfield',
    '#title'          => 'Public certificate',
    '#default_value'  => variable_get('yadpm_my_cert_file_path','/etc/apache2/openssl/paypal_cert.pem'),
    '#description'    => t('Path to your own public ssl certificate'),
  );
  $form['ssl']['yadpm_paypal_cert_file_path'] = array(
    '#type'           => 'textfield',
    '#title'          => 'Paypal public certificate',
    '#default_value'  => variable_get('yadpm_paypal_cert_file_path', $_SERVER['DOCUMENT_ROOT']. '/'. drupal_get_path('module', 'yadpm'). '/paypal_cert_pem.txt'),
    '#description'    => t('Path to the public paypal ssl certificate'),
  );
  $form['ssl']['yadpm_openssl_path'] = array(
    '#type'           => 'textfield',
    '#title'          => 'Path to the openssl executable',
    '#default_value'  => variable_get('yadpm_openssl_path','/usr/bin/openssl'),
    '#description'    => t('Path to the openssl executable file'),
  );
  $form['ssl']['yadpm_cert_id'] = array(
    '#type'           => 'textfield',
    '#title'          => 'Certificate ID',
    '#default_value'  => variable_get('yadpm_cert_id','K6MFZDCT4NH7J'),
    '#description'    => t('Paypal certificate ID given when you import your public certificate to paypal.'),
  );
  $form['ssl']['procedure'] = array(
    '#type' => 'fieldset',
    '#title' => 'Certificate generation procedure',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['ssl']['procedure']['notice'] = array(
    '#prefix' => '<pre>',
    '#suffix' => '</pre>',
    '#markup' => '
mkdir /etc/apache2/openssl
cd /etc/apache2/openssl
openssl genrsa -out paypal_key.pem 2048
openssl req -new -key paypal_key.pem -x509 -days 3650 -out paypal_cert.pem
chmod 600 paypal_*
',
  );

  return system_settings_form($form);
}

function yadpm_admin_form_validate($form, &$form_state) {
  if (!is_writable($form_state['values']['yadpm_logfilepath'])) {
    form_set_error('yadpm_logfilepath', "The path is not writable.");
  }
  if (!file_exists($form_state['values']['yadpm_my_key_file_path'])) {
    form_set_error('yadpm_my_key_file_path', "File not found.");
  }
  if (!file_exists($form_state['values']['yadpm_my_cert_file_path'])) {
    form_set_error('yadpm_my_cert_file_path', "File not found.");
  }
  if (!file_exists($form_state['values']['yadpm_paypal_cert_file_path'])) {
    form_set_error('yadpm_paypal_cert_file_path', "File not found.");
  }
  if (!file_exists($form_state['values']['yadpm_openssl_path'])) {
    form_set_error('yadpm_openssl_path', "File not found.");
  }
}
