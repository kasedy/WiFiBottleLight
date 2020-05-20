import React, { Component } from 'react';

import { Box, Switch, Slider, Select, InputLabel, FormControl } from '@material-ui/core';
import { WebSocketFormProps } from '../components';
import { BlockFormControlLabel } from '../components';
import { createStyles, Theme, WithStyles, withStyles } from '@material-ui/core/styles';

import { LightState } from './types';

const styles = (theme: Theme) => createStyles({
  shiftLeft: {
    textAlign: 'left'
  },
  labelWrapper: {
    width: '100%',
    paddingTop: theme.spacing(2),
  }
});

type LightStateSocketControllerFormProps = WebSocketFormProps<LightState> & WithStyles<typeof styles>;

class LightStateSocketControllerForm extends Component<LightStateSocketControllerFormProps> {

  handleValueChange(name: string) {
    const { data, saveData, setData } = this.props;
    return (event: any, value: any) => {
      setData({ ...data, [name]: value }, saveData);
    };
  }

  renderEffectListItems() {
    const { data } = this.props;
    return data.effect_list.map((name: any, index: any) => (
      <option key={index} value={index}>{name}</option>
    ));
  }

  setEffect = (event: any) => {
    const { data, saveData, setData } = this.props;
    setData({ ...data, 'effect': parseInt(event.target.value) }, saveData);
  }

  render() {
    const { data, classes } = this.props;
    return (
      <Box display="flex" alignItems="center" flexDirection="column">
          <BlockFormControlLabel
            control={
              <Switch
                checked={data.state}
                onChange={this.handleValueChange('state')}
                color="primary"
              />
            }
            label="Enable"
            labelPlacement='start'
            className={classes.labelWrapper}
          />
          <Box className={classes.labelWrapper}>
            <InputLabel className={classes.shiftLeft}>Brightness</InputLabel>
          </Box>
          <Slider 
            value={data.brightness}
            min={0}
            max={255}
            onChange={this.handleValueChange('brightness')}
            valueLabelFormat={(value) => `${Math.trunc((value + 0.5) / 256 * 100 + 0.5)}%` }
            valueLabelDisplay='auto' />
          <Box className={classes.labelWrapper}>
            <InputLabel className={classes.shiftLeft}>Effect speed</InputLabel>
          </Box>
          <Slider 
            value={data.speed}
            min={0}
            max={255}
            onChange={this.handleValueChange('speed')}
            valueLabelFormat={(value) => `${Math.trunc((value + 0.5) / 256 * 100 + 0.5)}%` }
            valueLabelDisplay='auto' />
          <Box className={classes.labelWrapper}>
            <InputLabel className={classes.shiftLeft}>Effect</InputLabel>
          </Box>
          <FormControl variant="outlined" margin="normal" fullWidth>
            <Select
              native
              value={data.effect}
              onChange={this.setEffect}>
              {this.renderEffectListItems()}
            </Select>
          </FormControl>      
      </Box>
    );
  }
}

export default withStyles(styles)(LightStateSocketControllerForm);