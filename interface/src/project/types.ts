export interface LightState {
  state: boolean;
  brightness: number;
  speed?: number;
  effect?: any;
  effect_list?: any;
}

export interface LightBrokerSettings { 
  unique_id : string;
  name: string;
  mqtt_path : string;
}
