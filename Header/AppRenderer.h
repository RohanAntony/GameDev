#ifndef APP_RENDERNODE_HEADER
#define APP_RENDERNODE_HEADER

#include "GaLib/SpriteInstance.h"
#include <map>

using std::map;
using GaLib::SpriteInstance;

class RenderNode {
	map<int, SpriteInstance*> list;	//should contain the list of sprites that need to be rendererd as per the id for 
	int spriteCount;
	bool render;
public:
	RenderNode() : render(false), spriteCount(0)
	{		
	}

	void setRender() {
		render = true;
	}

	void resetRender() {
		render = false;
	}

	bool renderRequired() {
		return render;
	}

	int addSpriteToNode(SpriteInstance* sprite) {
		list.insert();
	}
};

class RenderMap {
	RenderNode** nodes;
public:
	RenderMap(int width, int height) {
		nodes = new RenderNodes[height];
		for (int i = 0; i < height; i++)
			nodes[i] = new RenderNodes[width];
	}

};

#endif

