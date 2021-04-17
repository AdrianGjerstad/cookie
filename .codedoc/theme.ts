import {
  createTheme,
  DefaultCodeThemeLight
} from '@codedoc/core/transport';


export const theme = /*#__PURE__*/createTheme({
  light: {
    primary: '#000000'
  },
  dark: {
    primary: '#ffffff'
  },
  code: {
    wmbar: false,
    light: DefaultCodeThemeLight
  }
});
