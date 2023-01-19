#include "actor_node.h"
#include "pixel-transform.h"

G_DEFINE_TYPE_WITH_PRIVATE(ActorNode, actor_node, G_TYPE_OBJECT);

static guint _signals[signal_nums] = {0};

enum
{
    PROP_0,
    PROP_NUMS
};

static GParamSpec *props[PROP_NUMS];

static void actor_node_set_property(GObject *object, guint id, const GValue *value, GParamSpec *params)
{

}

static void actor_node_get_property(GObject *object, guint id, GValue *value, GParamSpec *params)
{

}

static void actor_node_dispose(GObject *object)
{

}

static void actor_node_finalize(GObject *object)
{

}

static void actor_node_class_init(ActorNodeClass *klass)
{
    GObjectClass *oclass = G_OBJECT_CLASS(klass);
    oclass->set_property = actor_node_set_property;
    oclass->get_property = actor_node_get_property;
    oclass->dispose = actor_node_dispose;
    oclass->finalize = actor_node_finalize;
}

static void actor_node_init(ActorNode *self)
{
    ActorNodePrivate *priv = actor_node_get_instance_private(self);
    priv->node = g_node_new(self);
    priv->transform = new_Transform;
}

ActorNode *actor_node_new(void)
{
    return g_object_new(ACTOR_NODE_TYPE, NULL);
}