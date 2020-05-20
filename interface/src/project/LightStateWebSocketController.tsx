import React, { Component } from 'react';

import { Paper, Typography } from '@material-ui/core';
import { LIGHT_SETTINGS_WEBSOCKET_ENDPOINT, PROJECT_NAME } from '../api';
import { WebSocketControllerProps, WebSocketFormLoader, webSocketController } from '../components';
import { createStyles, Theme, WithStyles, withStyles } from '@material-ui/core/styles';

import { LightState } from './types';
import LightStateSocketControllerForm from './LightStateSocketControllerForm';

const styles = (theme: Theme) => createStyles({
  content: {
    display: "flex",
    justifyContent: "center",
    flexDirection: "column",
    textAlign: "center",
    padding: theme.spacing(2),
    margin: theme.spacing(3),
    marginLeft: 'auto',
    marginRight: 'auto',
    maxWidth: theme.breakpoints.values.sm,
  },
});

type LightStateWebSocketControllerProps = WebSocketControllerProps<LightState> & WithStyles<typeof styles>;

class LightStateSocketController extends Component<LightStateWebSocketControllerProps> {

  render() {
    const { classes, ...rest } = this.props;
    return (
      <Paper className={classes.content}>
        <Typography variant="h4" gutterBottom>
          {PROJECT_NAME}
        </Typography>
        <WebSocketFormLoader
          {...rest}
          render={props => (
              <LightStateSocketControllerForm {...props} />
          )}
        />
      </Paper>
    )
  }
}

export default webSocketController(LIGHT_SETTINGS_WEBSOCKET_ENDPOINT, 100, withStyles(styles)(LightStateSocketController));