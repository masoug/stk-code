//
//  SuperTuxKart - a fun racing game with go-kart
//  Copyright (C) 2013 Lauri Kasanen
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 3
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include "graphics/light.hpp"

#include "graphics/callbacks.hpp"
#include "graphics/glwrap.hpp"
#include "graphics/irr_driver.hpp"
#include "graphics/material_manager.hpp"
#include "graphics/material.hpp"
#include "graphics/rtts.hpp"
#include "graphics/shaders.hpp"

using namespace video;
using namespace scene;
using namespace core;

IMesh * LightNode::sphere = NULL;
SMaterial LightNode::mat;
aabbox3df LightNode::box;


LightNode::LightNode(scene::ISceneManager* mgr, float radius, float r, float g, float b):
                     ISceneNode(mgr->getRootSceneNode(), mgr, -1)
{
    if (!sphere)
    {
        mat.Lighting = false;
        mat.MaterialType = irr_driver->getShaders()->getShader(ES_COLORIZE);

        mat.setTexture(0, irr_driver->getRTTs()->getRTT(RTT_NORMAL));
        mat.setTexture(1, irr_driver->getRTTs()->getRTT(RTT_DEPTH));

        mat.setFlag(EMF_TEXTURE_WRAP, ETC_CLAMP_TO_EDGE);
        mat.setFlag(EMF_BILINEAR_FILTER, false);
        mat.setFlag(EMF_ZWRITE_ENABLE, false);

        sphere = mgr->getGeometryCreator()->createSphereMesh(1, 16, 16);
        box = sphere->getBoundingBox();
    }

    setScale(vector3df(radius));

    m_color[0] = r;
    m_color[1] = g;
    m_color[2] = b;
}

LightNode::~LightNode()
{
}

void LightNode::render()
{
    IVideoDriver * const drv = irr_driver->getVideoDriver();
    drv->setTransform(ETS_WORLD, AbsoluteTransformation);
    drv->setMaterial(mat);

    drv->drawMeshBuffer(sphere->getMeshBuffer(0));
}

void LightNode::OnRegisterSceneNode()
{ // This node is only drawn manually.
}