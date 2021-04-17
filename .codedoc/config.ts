
import { configuration } from '@codedoc/core';

import { theme } from './theme';


export const config = /*#__PURE__*/configuration({
  theme,                                  // --> add the theme. modify `./theme.ts` for changing the theme.
  
  page: {
    title: {
      base: 'Cookie'                      // --> the base title of your doc pages
    }
  },

  misc: {
    github: {
      user: 'AdrianGjerstad',
      repo: 'cookie'
    }
  },
  
  dest: {
    namespace: '/cookie'
  }
});
