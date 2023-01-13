#ifndef ACTOR_NODE_H
#define ACTOR_NODE_H
#include <glib-object.h>
#include "rmath.h"

G_BEGIN_DECLS

typedef struct _ActorNode ActorNode;
typedef struct _ActorNodePrivate ActorNodePrivate;
typedef struct _ActorNodeClass ActorNodeClass;

#define ACTOR_NODE_TYPE actor_node_get_type()
G_DECLARE_DERIVABLE_TYPE(ActorNode, actor_node, ACTOR, NODE, GObject);

typedef enum {
    signal_none = 0,
    signal_nums
}actor_node_signals;

struct _ActorNodePrivate {
    GObject parent_instance;
    GNode *node;
    rtransform transform;
};

struct _ActorNodeClass {
    GObjectClass parent_class;
};

ActorNode *actor_node_new(void);

G_END_DECLS

#endif