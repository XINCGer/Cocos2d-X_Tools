#include "NinePatch.h"
USING_NS_CC;
#define PATCH_WIDTH 200
#define PATCH_HEIGHT 200
NinePatch* NinePatch::createPatch(int width, int height, int borderSize, Point position)
{
	NinePatch* patch = NinePatch::create();
	if (patch)
	{
		patch->initPatch(width, height, borderSize, position);
		return patch;
	}
	CC_SAFE_DELETE(patch);
	return NULL;
}
void NinePatch::initPatch(int width, int height, int borderSize, Point position)
{
	// 左上角
	auto* patch1 = Sprite::create("patch.png", Rect(0, 0, borderSize, borderSize));
	patch1->setAnchorPoint(Vec2(0, 0));
	patch1->setPosition(position.x, position.y + height - borderSize);
	addChild(patch1);
	// 右上角
	auto* patch3 = Sprite::create("patch.png", Rect(PATCH_WIDTH - borderSize, 0, borderSize, borderSize));
	patch3->setAnchorPoint(Vec2(0, 0));
	patch3->setPosition(position.x + width - borderSize, position.y + height - borderSize);
	addChild(patch3);
	// 左下角
	auto* patch7 = Sprite::create("patch.png", Rect(0, PATCH_HEIGHT - borderSize, borderSize, borderSize));
	patch7->setAnchorPoint(Vec2(0, 0));
	patch7->setPosition(position.x, position.y);
	addChild(patch7);
	// 右下角
	auto* patch9 = Sprite::create("patch.png", Rect(PATCH_WIDTH - borderSize, PATCH_HEIGHT - borderSize, borderSize, borderSize));
	patch9->setAnchorPoint(Vec2(0, 0));
	patch9->setPosition(position.x + width - borderSize, position.y);
	addChild(patch9);
	
	// 顶部分栏
	auto* patch2 = Sprite::create("patch.png", Rect(borderSize, 0, PATCH_WIDTH - borderSize * 2, borderSize));
	patch2->setAnchorPoint(Vec2(0, 0));
	patch2->setPosition(position.x + borderSize, position.y + height - borderSize);
	patch2->setScaleX((float)(width - borderSize * 2) / (PATCH_WIDTH - borderSize * 2));
	addChild(patch2);
	// 左侧分栏
	auto* patch4 = Sprite::create("patch.png", Rect(0, borderSize, borderSize, PATCH_HEIGHT - borderSize * 2));
	patch4->setAnchorPoint(Vec2(0, 0));
	patch4->setPosition(position.x, position.y + borderSize);
	patch4->setScaleY((float)(height - borderSize * 2) / (PATCH_HEIGHT - borderSize * 2));
	addChild(patch4);
	// 右侧分栏
	auto* patch6 = Sprite::create("patch.png", Rect(PATCH_HEIGHT - borderSize, borderSize, borderSize, PATCH_HEIGHT - borderSize * 2));
	patch6->setAnchorPoint(Vec2(0, 0));
	patch6->setPosition(position.x + width - borderSize, position.y + borderSize);
	patch6->setScaleY((float)(height - borderSize * 2) / (PATCH_HEIGHT - borderSize * 2));
	addChild(patch6);
	// 底部
	auto* patch8 = Sprite::create("patch.png", Rect(borderSize, PATCH_HEIGHT - borderSize, PATCH_WIDTH - borderSize * 2, borderSize));
	patch8->setAnchorPoint(Vec2(0, 0));
	patch8->setPosition(position.x + borderSize, position.y);
	patch8->setScaleX((float)(width - borderSize * 2) / (PATCH_WIDTH - borderSize * 2));
	addChild(patch8);
	// 中间填充部分
	auto* patch5 = Sprite::create("patch.png", Rect(borderSize, borderSize, PATCH_WIDTH - borderSize*2, PATCH_HEIGHT - borderSize*2));
	patch5->setAnchorPoint(Vec2(0, 0));
	patch5->setPosition(position.x + borderSize, position.y + borderSize);
	patch5->setScale((float)(width - borderSize * 2) / (PATCH_WIDTH - borderSize * 2), (float)(height - borderSize * 2) / (PATCH_HEIGHT - borderSize * 2));
	addChild(patch5);
}