import type {HostComponent,ViewProps} from 'react-native';
import codegenNativeComponent from 'react-native/Libraries/Utilities/codegenNativeComponent';
import codegenNativeCommands from "react-native/Libraries/Utilities/codegenNativeCommands";
import type {
  BubblingEventHandler,
  Double,
  Int32,
  DirectEventHandler,
  Float
  } from 'react-native/Libraries/Types/CodegenTypes';
  
export interface NativeProps extends ViewProps {
  onRefresh?:DirectEventHandler<VoidEventData>,
  onRefreshIdle?:DirectEventHandler<VoidEventData>,
  onReleaseToRefresh?:DirectEventHandler<VoidEventData>,
  onPulling?:DirectEventHandler<EventData>
  // 添加其它 props
}
export type EventData = Readonly<{
  percent: Float;
  offset: Float;
  headerHeight: Float;
}>;
export default codegenNativeComponent<NativeProps>(
  'MJRefresh',
) as HostComponent<NativeProps>;
export type VoidEventData = Readonly<{}>;

