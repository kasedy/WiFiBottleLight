import { ENDPOINT_ROOT, WEB_SOCKET_ROOT } from './Env';

export const NTP_STATUS_ENDPOINT = ENDPOINT_ROOT + "ntpStatus";
export const NTP_SETTINGS_ENDPOINT = ENDPOINT_ROOT + "ntpSettings";
export const AP_SETTINGS_ENDPOINT = ENDPOINT_ROOT + "apSettings";
export const AP_STATUS_ENDPOINT = ENDPOINT_ROOT + "apStatus";
export const SCAN_NETWORKS_ENDPOINT = ENDPOINT_ROOT + "scanNetworks";
export const LIST_NETWORKS_ENDPOINT = ENDPOINT_ROOT + "listNetworks";
export const WIFI_SETTINGS_ENDPOINT = ENDPOINT_ROOT + "wifiSettings";
export const WIFI_STATUS_ENDPOINT = ENDPOINT_ROOT + "wifiStatus";
export const OTA_SETTINGS_ENDPOINT = ENDPOINT_ROOT + "otaSettings";
export const MQTT_SETTINGS_ENDPOINT = ENDPOINT_ROOT + "mqttSettings";
export const MQTT_STATUS_ENDPOINT = ENDPOINT_ROOT + "mqttStatus";
export const SYSTEM_STATUS_ENDPOINT = ENDPOINT_ROOT + "systemStatus";
export const SIGN_IN_ENDPOINT = ENDPOINT_ROOT + "signIn";
export const VERIFY_AUTHORIZATION_ENDPOINT = ENDPOINT_ROOT + "verifyAuthorization";
export const SECURITY_SETTINGS_ENDPOINT = ENDPOINT_ROOT + "securitySettings";
export const RESTART_ENDPOINT = ENDPOINT_ROOT + "restart";
export const FACTORY_RESET_ENDPOINT = ENDPOINT_ROOT + "factoryReset";

export const HOME_ASSISTANT_SETTINGS_ENDPOINT = ENDPOINT_ROOT + "ha";
export const LIGHT_SETTINGS_WEBSOCKET_ENDPOINT = WEB_SOCKET_ROOT + "light";