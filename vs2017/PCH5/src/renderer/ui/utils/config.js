/**
 * Created by lpy on 2017/10/23.
 */
const config = {
  defaultContentElement: null,
  defaultDialogConfirmText: null,
  defaultIconPack: 'mdi',
  defaultSnackbarDuration: 3500,
  defaultToastDuration: 2000,
  defaultTooltipType: 'is-primary',
  defaultTooltipAnimated: false,
  defaultInputAutocomplete: 'on'
}

export default config

export const setOptions = options => {
  this.config = options
}
