import React, { Component } from 'react';

import {restController, RestControllerProps, RestFormLoader, SectionContent } from '../components';
import { HOME_ASSISTANT_SETTINGS_ENDPOINT } from '../api';

import HomeAssistantSettingsForm from './HomeAssistantSettingsForm';
import { HomeAssistantSettings } from './types';

type HomeAssistantSettingsControllerProps = RestControllerProps<HomeAssistantSettings>;

class HomeAssistantSettingsController extends Component<HomeAssistantSettingsControllerProps> {

  componentDidMount() {
    this.props.loadData();
  }

  render() {
    return (
      <SectionContent title="Home Assistant Settings" titleGutter>
        <RestFormLoader
          {...this.props}
          render={formProps => <HomeAssistantSettingsForm {...formProps} />}
        />
      </SectionContent>
    )
  }

}

export default restController(HOME_ASSISTANT_SETTINGS_ENDPOINT, HomeAssistantSettingsController);
