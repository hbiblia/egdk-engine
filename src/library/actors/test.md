
ActorNode *parent = actor_node_new();

ActorNode *node1 = actor_node_shape_rectangle();
actor_node_shape_set_color(node1, 200,0,200);
actor_node_append(parent, node1);
{
    ActorNode *node2 = actor_node_shape_rectangle();
    actor_node_shape_set_color(node2, 200,0,200);
    actor_node_append(node1, node2);
    {
        ActorNode *node3 = actor_node_shape_rectangle();
        actor_node_shape_set_color(node3, 100,0,100);
        actor_node_append(node2, node3);
        {
            ActorNode *node4 = actor_node_shape_rectangle();
            actor_node_shape_set_color(node4, 25, 0, 25);
            actor_node_append(node3, node4);
        }
    }
}


ActorPrivate {
    Node node
    String name_uniqu;
}

<!-- ACTOR NODE -->

Node *node = node_new();

Actor *actor1 = actor_rectangle_new(100, 100);
Actor *actor2 = actor_rectangle_new(50, 50);
actor_add_child(actor1, actor2);

<!-- ACTOR PURO -->
Actor *scene = actor_scene_new();
actor_scene_set_main(scene);

Actor *container = actor_container_new();
actor_scene_add_child(scene, container);
{
    Actor *rect = actor_shape_rect_new(100, 100);
    actor_shape_set_color(rect, 200, 0, 200);
    actor_transform_set_rotation_z(rect, 25);
    actor_container_add_child(container, rect);

    Actor *rect2 = actor_shape_rect_new(100, 100);
    actor_shape_set_color(rect2, 100, 50, 200);
    actor_container_add_child(container, rect2);
}

while(1) {
    actor_scene_progress();

    static double rotz = 0;
    rotz += 0.1f * delta;
    actor_transform_set_rotation_z(container, rotz);
    // or
    actor_transform_add_rotation_z(container, (0.1f * delta));
}