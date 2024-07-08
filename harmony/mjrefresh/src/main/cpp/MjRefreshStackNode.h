#pragma once

#include "RNOH/arkui/ArkUINode.h"

namespace rnoh {
class MjRefreshStackNodeDelegate {
 public:
  virtual ~MjRefreshStackNodeDelegate() = default;
  virtual void onClick() {};
};

class MjRefreshStackNode : public ArkUINode {
 protected:
  MjRefreshStackNodeDelegate* m_stackNodeDelegate;

 public:
  MjRefreshStackNode();
  ~MjRefreshStackNode() override;

  void insertChild(ArkUINode& child, std::size_t index);
  void removeChild(ArkUINode& child);
  void onNodeEvent(ArkUI_NodeEventType eventType, EventArgs& eventArgs)
      override;
  void onClick();
  void setStackNodeDelegate(MjRefreshStackNodeDelegate* MjRefreshStackNodeDelegate);
  MjRefreshStackNode& setMargin(float left, float top, float right, float bottom);
  MjRefreshStackNode& setAlign(int32_t align);
};

} // namespace rnoh