#include "StdActions.h"
#include <iostream>

DelayAction::DelayAction(const Animation* parent, int duration)
    : TimedAction(parent, duration)
{
    mIsHalting = true;
}

//-----------------------------------------------------------------------

WaitAction::WaitAction(const Animation* parent) {
    parent = mParent;
    mIsHalting = true;
}

bool WaitAction::IsResolved() const {
    return mParent->GetNumActiveActions() <= 1; // the 1 is this wait action
}

//-----------------------------------------------------------------------

RunAsyncAnimationAction::RunAsyncAnimationAction(Animation* parent, std::shared_ptr<Animation> animation) {
    mParent = parent;
    mAnimation = animation;
}

void RunAsyncAnimationAction::Initialize() {
    mAnimation->Initialize(mParent->GetFrameRate());
    mParent->AddChildAnimation(mAnimation.get());
}

bool RunAsyncAnimationAction::IsResolved() const {
    return true;
}

//-----------------------------------------------------------------------

RunAnimationAction::RunAnimationAction(Animation* parent, std::shared_ptr<Animation> animation)
    : RunAsyncAnimationAction(parent, animation)
{
    mIsHalting = true;
}

bool RunAnimationAction::IsResolved() const {
    return mAnimation->IsComplete();
}
