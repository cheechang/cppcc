/**
 * Created by lpy on 2017/10/23.
 */
import Avatar from './components/avatar';
import Button from './components/button';
import Input from './components/input';
import Field from './components/field';
import Select from './components/select';
import Badge from './components/badge';
import Title from './components/title';
import Tooltip from './components/tooltip';
import Modal from './components/modal';
import Message from './components/message';
import Menu from './components/menu';
import Checkbox from './components/checkbox';
import Navbar from './components/navbar';
import Prompt from './components/prompt';
import Icon from './components/icon';
import Switch from './components/switch';
import Dialog from './components/dialog';
import Toast from './components/toast';
import CustomIcon from './components/customicon';
import Progress from './components/progress';
import AutoComplete from './components/autocomplete';
import {
  Card,
  CardList
} from './components/card';
import {
  Radio,
  RadioGroup
} from './components/radio';
import {
  Tabs,
  TabItem
} from './components/tab';
import config, {
  setOptions
} from './utils/config';

const vrvui = {
  Avatar,
  Button,
  Input,
  Card,
  CardList,
  Checkbox,
  Field,
  Select,
  Badge,
  Title,
  Tooltip,
  Modal,
  Message,
  Menu,
  Radio,
  RadioGroup,
  Navbar,
  Tabs,
  TabItem,
  Prompt,
  Icon,
  Switch,
  CustomIcon,
  Progress,
  AutoComplete
};

vrvui.install = (Vue, options = {}) => {
  setOptions(Object.assign(config, options));

  for (const componentName in vrvui) {
    const component = vrvui[componentName];

    if (component && componentName !== 'install') {
      Vue.component(component.name, component);
    }
  }
  Vue.prototype.$dialog = Dialog
  Vue.prototype.$toast = Toast
};

export default vrvui

export {
  Dialog,
  Toast
}
