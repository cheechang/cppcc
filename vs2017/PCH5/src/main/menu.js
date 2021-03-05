import { app, Menu, shell, globalShortcut } from 'electron'
// import screenShot from './screenShot'

function createMenu() {
  const  template  =  [
    {
      label:  'Edit',
      submenu:  [
        { role:  'undo' },
        { role:  'redo' },
        { type:  'separator' },
        { role:  'cut' },
        { role:  'copy' },
        { role:  'paste' },
        { role:  'pasteandmatchstyle' },
        { role:  'delete' },
        { role:  'selectall' }
      ]
    },
    {
      label:  'Viewing',
      submenu:  [
        { role:  'reload' },
        { role:  'forcereload' },
        { role:  'toggledevtools' },
        { type:  'separator' },
        { role:  'resetzoom' },
        { role:  'zoomin' },
        { role:  'zoomout' },
        { type:  'separator' },
        { role:  'togglefullscreen' }
      ]
    },
    {
      role:  'window',
      submenu:  [
        { role:  'minimize' },
        { role:  'close' }
      ]
    },
    {
      role:  'help',
      submenu:  [
        {
          label:  'Learn More',
          click ()  { shell.openExternal('https://vrv.linkdood.cn')  }
        }
      ]
    }
  ]

  const  menu  =  Menu.buildFromTemplate(template)
  Menu.setApplicationMenu(menu)
}
// let scr = globalShortcut.register('Alt+A', ()=>{
//   screenShot();
// })
export default createMenu