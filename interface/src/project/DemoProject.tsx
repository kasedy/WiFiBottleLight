import React, { Component } from 'react';
import { RouteComponentProps } from 'react-router-dom'

import { PROJECT_PATH } from '../api';
import { MenuAppBar } from '../components';
import { AuthenticatedRoute } from '../authentication';

import LightStateWebSocketController from './LightStateWebSocketController';

class DemoProject extends Component<RouteComponentProps> {
  render() {
    return (
      <MenuAppBar sectionTitle="Control">
        <AuthenticatedRoute exact path={`/${PROJECT_PATH}/`} component={LightStateWebSocketController} />
      </MenuAppBar>
    )
  }

}

export default DemoProject;
