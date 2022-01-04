#ifndef ECSCOMPONENTS_H
#define ECSCOMPONENTS_H

#include "blocklook.component.h"
#include "camera.component.h"
#include "control.component.h"
#include "debug.component.h"
#include "light.component.h"
#include "movement.component.h"
#include "physics.component.h"
#include "position.component.h"

#define _ECS_DECL_COMPONENT(_name)                                            \
  extern void _name##_init ();                                                \
  _name##_init (ecs);

static inline void
_ecs_init_internal (struct ECS *ecs)
{
  _ECS_DECL_COMPONENT (comp_position);
  _ECS_DECL_COMPONENT (comp_camera);
  _ECS_DECL_COMPONENT (comp_control);
  _ECS_DECL_COMPONENT (comp_physics);
  _ECS_DECL_COMPONENT (comp_movement);
  _ECS_DECL_COMPONENT (comp_blocklook);
  _ECS_DECL_COMPONENT (comp_debug);
  _ECS_DECL_COMPONENT (comp_light);
}

#define ECSCOMPONENT_LAST C_LIGHT
enum ECSComponent
{
  C_POSITION = 0,
  C_CAMERA,
  C_CONTROL,
  C_PHYSICS,
  C_MOVEMENT,
  C_BLOCKLOOK,
  C_DEBUG,
  C_LIGHT
};

#endif
