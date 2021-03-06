/******************************************************************************
 * Spine Runtimes Software License
 * Version 2.1
 * 
 * Copyright (c) 2013, Esoteric Software
 * All rights reserved.
 * 
 * You are granted a perpetual, non-exclusive, non-sublicensable and
 * non-transferable license to install, execute and perform the Spine Runtimes
 * Software (the "Software") solely for internal use. Without the written
 * permission of Esoteric Software (typically granted by licensing Spine), you
 * may not (a) modify, translate, adapt or otherwise create derivative works,
 * improvements of the Software or develop new applications using the Software
 * or (b) remove, delete, alter or obscure any trademarks or any copyright,
 * trademark, patent or other intellectual property or proprietary rights
 * notices on or in the Software, including any copy thereof. Redistributions
 * in binary or source form must include this license and terms.
 * 
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ESOTERIC SOFTARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#ifndef SPINE_CCSKELETONANIMATION_H_
#define SPINE_CCSKELETONANIMATION_H_

#include <spine/spine.h>
#include <spine/CCSkeleton.h>
#include "cocos2d.h"

namespace spine {

class CCSkeletonAnimation;
typedef void (cocos2d::CCObject::*SEL_AnimationStateEvent)(spine::CCSkeletonAnimation* node, int trackIndex, spEventType type, spEvent* event, int loopCount);
#define animationStateEvent_selector(_SELECTOR) (SEL_AnimationStateEvent)(&_SELECTOR)

/** Draws an animated skeleton, providing an AnimationState for applying one or more animations and queuing animations to be
  * played later. */
class CCSkeletonAnimation: public CCSkeleton {
public:
	spAnimationState* state;

	static CCSkeletonAnimation* createWithData (spSkeletonData* skeletonData);
	static CCSkeletonAnimation* createWithFile (const char* skeletonDataFile, spAtlas* atlas, float scale = 0);
	static CCSkeletonAnimation* createWithFile (const char* skeletonDataFile, const char* atlasFile, float scale = 0);

	CCSkeletonAnimation (spSkeletonData* skeletonData);
	CCSkeletonAnimation (const char* skeletonDataFile, spAtlas* atlas, float scale = 0);
	CCSkeletonAnimation (const char* skeletonDataFile, const char* atlasFile, float scale = 0);

	virtual ~CCSkeletonAnimation ();

	virtual void update (float deltaTime);

	void setAnimationStateData (spAnimationStateData* stateData);
	void setMix (const char* fromAnimation, const char* toAnimation, float duration);

	void setAnimationListener (CCObject* instance, SEL_AnimationStateEvent method);
	spTrackEntry* setAnimation (int trackIndex, const char* name, bool loop);
	spTrackEntry* addAnimation (int trackIndex, const char* name, bool loop, float delay = 0);
	spTrackEntry* getCurrent (int trackIndex = 0);
	void clearTracks ();
	void clearTrack (int trackIndex = 0);

	virtual void onAnimationStateEvent (int trackIndex, spEventType type, spEvent* event, int loopCount);

protected:
	CCSkeletonAnimation ();

private:
	typedef CCSkeleton super;
	CCObject* listenerInstance;
	SEL_AnimationStateEvent listenerMethod;
	bool ownsAnimationStateData;

	void initialize ();
};

}

#endif /* SPINE_CCSKELETONANIMATION_H_ */
