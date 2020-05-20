import React from 'react';
import { TextValidator, ValidatorForm } from 'react-material-ui-form-validator';
import { withStyles, createStyles, Theme, WithStyles } from '@material-ui/core/styles';
import { Box, Typography } from '@material-ui/core';

import SaveIcon from '@material-ui/icons/Save';

import { RestFormProps, FormActions, FormButton } from '../components';

import { HomeAssistantSettings } from './types';

const styles = (theme: Theme) => createStyles({
  '@global': {
    code: {
      fontFamily: "Consolas, Monaco, 'Andale Mono', 'Ubuntu Mono', monospace"
    },
    'p > code': {
      fontWeight: theme.typography.fontWeightBold,
      backgroundColor: 'rgba(255, 229, 100, 0.2)',
    },
    'pre > code': {
      color: theme.palette.info.contrastText,
    }
  },
  token: {
    color: theme.palette.warning.light
  }
});

type HomeAssistantSettingsFormProps = RestFormProps<HomeAssistantSettings> & WithStyles<typeof styles>;

class HomeAssistantSettingsForm extends React.Component<HomeAssistantSettingsFormProps> {
  render() {
    const { data, handleValueChange, saveData, loadData, classes } = this.props;
    return (
      <Box>
        <Box mt={3}>
          <Typography>To make it work enable auto discovery feature in <code>configuration.yaml</code> of Home Assistant:</Typography>
        </Box>
        <Box component="pre" bgcolor="info.main" overflow="auto" borderRadius={4} p={2} mt={2} mb={3}>
          <code>
            <span className={classes.token}>mqtt</span>:{"\n"}
            {"  "}<span className={classes.token}>discovery</span>: true{"\n"}
            {"  "}<span className={classes.token}>discovery_prefix</span>: homeassistant{"\n"}
          </code>
        </Box>
        <ValidatorForm onSubmit={saveData}>
          <TextValidator
            // validators={['required']}
            // errorMessages={['Home Assistant device display is required']}
            name="name"
            label="Device disaply name"
            fullWidth
            variant="outlined"
            value={data.name}
            onChange={handleValueChange('name')}
            margin="normal"
          />
          <FormActions>
            <FormButton startIcon={<SaveIcon />} variant="contained" color="primary" type="submit">
              Save
            </FormButton>
            <FormButton variant="contained" color="secondary" onClick={loadData}>
              Reset
            </FormButton>
          </FormActions>
        </ValidatorForm>
      </Box>
    );
  }
}

export default withStyles(styles)(HomeAssistantSettingsForm);
