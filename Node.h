//
// Created by simon on 2021/06/27.
//

#ifndef NBODY_ALT_NODE_H
#define NBODY_ALT_NODE_H

struct Node {
    double centre_x, centre_y; // Centre of quadrant
    //double relX, relY; // Not sure about this
    double side; // Size of orig quadrant
    bool is_parent;
    bool is_empty;
    int id;

    double mass;
    // Centre of mass
    double com_x, com_y;

    struct Node* child_nodes[4];

//    struct Node *node_NE;
//    struct Node *node_SE;
//    struct Node *node_NW;
//    struct Node *node_SW;

    struct Body *body;
};

#define NW 0
#define NE 1
#define SE 2
#define SW 3

struct Node *InitTree(double min_pos, double max_pos);
struct Node* InitNode(int id, double centre_x, double centre_y, double side);
void ResetTree(struct Node* root_node);
void InsertBody(struct Node* node, struct Body* body);
void SplitNode(struct Node* split_node);
struct Node* GetNodeByQuadrant(struct Node * node, int quadrant);
int GetQuadrant(struct Node* node, struct Body* body);
void PrintTree(struct Node* node, int layer, int parent_id);
void CompCentreOfMasses(struct Node* node);
void TreeToDotFile(struct Node* root_node, FILE* fp);
double UpdateForceOnBodyByBody(struct Body* body, struct Body* other_body);
void CompForce(struct Body* body, struct Node* node);

#endif //NBODY_ALT_NODE_H