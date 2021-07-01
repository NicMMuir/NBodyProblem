#include "header.h"
#define IS_LOGGING_NODE false
#define THETA 1.0
#define G 9.8

// I.e. intialize head node
struct Node *InitTree(double min_pos, double max_pos){
    double size = max_pos - min_pos;
    if (size < 0){ // Effectively abs
        size *= -1;
    }
    double centre_x = (max_pos + min_pos)/2.0, centre_y = (max_pos + min_pos)/2.0;
    struct Node* head_node = InitNode(0, centre_x, centre_y, size);
//    struct Node * new_node = malloc (sizeof (struct Node));
//    new_node->centre_x = size/2.0;
//    new_node->centre_y = size/2.0;
//    new_node->side = size;
//    new_node->is_empty = true;
//    new_node->is_parent = false;
    return head_node;
}

struct Node* InitNode(int id, double centre_x, double centre_y, double side){
    struct Node* new_node = (struct Node*) malloc(sizeof (struct Node));
    new_node->id = id;
    new_node->centre_x = centre_x;
    new_node->centre_y = centre_y;
    new_node->side = side;
    new_node->is_parent = false;
    new_node->is_empty = true;
    new_node->body = NULL;
    return new_node;
}

// TODO - This is not working properly
// Maybe pass pointer by reference? E.g. pointer to pointer
void ResetTree(struct Node* node){
    // Recursively free all nodes
    if (node->is_parent) {
        for (int i = 0; i<4; i++){
            ResetTree(node->child_nodes[i]);
        }
    }
    free(node);
    node = NULL;
}

// Inserts body into tree and creates required nodes
void InsertBody(struct Node* node, struct Body* body) {
    // If node is empty and has no children add body
    if (node->is_parent == false && node->is_empty) {
        node->is_empty=false;
        node->body = body;
    } else if (node->is_parent){
        // Find correct quadrant to add to
        struct Node* quadrant_child = GetNodeByQuadrant(node, GetQuadrant(node, body));
        InsertBody(quadrant_child, body);
    }else if (node->is_empty == false){ // I.e. has body
        SplitNode(node);
        InsertBody(node, node->body); // Body already in node must be reinserted into tree at correct place
        node->is_empty = true;
        node->body = NULL;
        InsertBody(node, body);
    }
}

// Create and set child nodes
void SplitNode(struct Node* split_node){
    double half_side = split_node->side * 0.5;
    double x = split_node->centre_x, y = split_node->centre_y;
    split_node->is_parent = true;
    // split_node->is_empty = false;

    double new_side = split_node->side * 0.5;

    // NW
    split_node->child_nodes[NW] = InitNode(1,x - half_side/2,y-half_side/2,half_side);
    // NE
    split_node->child_nodes[NE] = InitNode(2,x + half_side/2,y-half_side/2,half_side);
    // SW
    split_node->child_nodes[SW] = InitNode(3,x - half_side/2,y+half_side/2,half_side);
    // SE
    split_node->child_nodes[SE] = InitNode(4,x + half_side/2,y+half_side/2,half_side);
}

/*
 *  <-------side-------->
 *
 *  |   NW   |   NE    |
 *  -------(x,y)---------
 *  |   SW   |   SE    |
 */


struct Node* GetNodeByQuadrant(struct Node * node, int quadrant){
    return node->child_nodes[quadrant]; // Will give error if quadrant >= 4 though
}

int GetQuadrant(struct Node* node, struct Body* body){
    double node_x = node->centre_x;
    double node_y = node->centre_y;

    double body_x = body->x;
    double body_y = body->y;

    if (body_x <= node_x  && body_y <= node_y){ // NW
        if (IS_LOGGING_NODE) {printf("Body %d is in NW quadrant of node %d\n", body->id, node->id);}
        return NW;
    } else if (body_x > node_x && body_y  <= node_y ){ // NE
        if (IS_LOGGING_NODE) {printf("Body %d is in NE quadrant of node %d\n", body->id, node->id);}
        return NE;
    } else if ( body_x > node_x && body_y > node_y){ // SE
        if (IS_LOGGING_NODE) {printf("Body %d is in SE quadrant of node %d\n", body->id, node->id);}
        return SE;
    } else { // SW
        if (IS_LOGGING_NODE) {printf("Body %d is in SW quadrant of node %d", body->id, node->id);}
        return SW;
    }
}

// com_x = (m1*x1 + m2*x2 + ...)/(m1+m2+m3+...)

void CompCentreOfMasses(struct Node* node){
    if (!node->is_parent && !node->is_empty){
        node->mass = node->body->mass;
        node->com_x = node->body->x;
        node->com_y = node->body->y;
    } else if(node->is_parent){
        double tmp_mass = 0;
        double tmp_com_x = 0, tmp_com_y = 0;
        for (int i = 0; i<4; i++){
            CompCentreOfMasses(node->child_nodes[i]);
            tmp_mass += node->child_nodes[i]->mass;
            tmp_com_x += node->child_nodes[i]->mass * node->child_nodes[i]->com_x;
            tmp_com_y += node->child_nodes[i]->mass * node->child_nodes[i]->com_y;
        }
        node->mass = tmp_mass;
        if (tmp_mass!=0){
            node->com_x = tmp_com_x/tmp_mass;
            node->com_y = tmp_com_y/tmp_mass;
        } else {
            fprintf(stderr,"Mass is zero - an error occurred\n");
        }
    } else {
        // Note: These must be zero
        node->mass = 0;
        node->com_x = 0;
        node->com_y = 0;
    }
}

void PrintTree(struct Node* node, int layer, int parent_id){
    if (node->is_parent) {
        for (int i = 0; i < 4; i++) {
            PrintTree(node->child_nodes[i], layer + 1, node->id);
        }
    } else {
        if (node->is_empty) {
            // No body Do nothing
        } else {
            printf("###############\n");
            printf("#  LAYER %d   #\n", layer);
            printf("# Parent ID: %d#\n",parent_id);
            printf("###############\n");
            PrintBody(node->body);
        }
    }
}

void NodeToDotFile(struct Node* curr_node, FILE* fp){
    if (curr_node->is_empty) { // If not leaf node
        fprintf(fp, "%lf_%lf [label=\"(%lf, %lf)\nmass: %lf, com: (%lf, %lf)\",shape=box];\n", curr_node->centre_x,
                curr_node->centre_y, curr_node->centre_x, curr_node->centre_y,
                curr_node->mass, curr_node->com_x, curr_node->com_y);
    } else { // If leaf node
        fprintf(fp, "%lf_%lf [label=\"(%lf, %lf)\n"
                    "-------------------------------------\n"
                    "pos: (%lf, %lf)\nvel: (%lf, %lf)\nmass: %lf\",shape=oval];\n",
                curr_node->centre_x, curr_node->centre_y, curr_node->centre_x, curr_node->centre_y,
                curr_node->body->x, curr_node->body->y,
                curr_node->body->vel_x, curr_node->body->vel_y, curr_node->body->mass);
    }

    if (curr_node->is_parent) {
        for (int i = 0; i<4; i++){
            struct Node* child_node = curr_node->child_nodes[i];
            fprintf(fp, "%lf_%lf -- %lf_%lf; \n", curr_node->centre_x,
                    curr_node->centre_y, child_node->centre_x, child_node->centre_y);
            NodeToDotFile(child_node, fp);
        }
    }
}

void TreeToDotFile(struct Node* root_node, FILE* fp){
    fprintf(fp, "graph n_body_graph {\n");
    NodeToDotFile(root_node, fp);
    fprintf(fp, "}\n");
}

// sqrt is expensive operation, thus if Dist is going to be squared anyway don't use sqrt
double DistSquared(double x1, double x2, double y1, double y2){
    return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}

double Dist(double x1, double x2, double y1, double y2){
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}
/*
 * https://en.wikipedia.org/wiki/Newton%27s_law_of_universal_gravitation
 * https://math.stackexchange.com/questions/12745/how-do-you-calculate-the-unit-vector-between-two-points
 *
 */

// body will have its force values updated based off interaction with other_body
// Force of other_body on body
double UpdateForceOnBodyByBody(struct Body* body, struct Body* other_body){
    double force_x, force_y;
    double unit_vec_x, unit_vec_y;
    double dist_squared = DistSquared(body->x, other_body->x, body->y, other_body->y);
    if (dist_squared!=0){ // Otherwise divide by zero -> if bodies are same
        double force_scalar = - G * (body->mass * other_body->mass)/dist_squared;
        double dist = sqrt(dist_squared);
        unit_vec_x = (body->x - other_body->x)/dist;
        unit_vec_y = (body->y - other_body->y)/dist;

        body->force_x += force_scalar * unit_vec_x;
        body->force_y += force_scalar * unit_vec_y;
    }
}

// body will have its force values updated based off approximation of interaction with node
double UpdateForceOnBodyByNode(struct Body* body, struct Node* node){
    double force_x, force_y;
    double unit_vec_x, unit_vec_y;
    double dist_squared = DistSquared(body->x, node->com_x, body->y, node->com_y);
    double force_scalar = - G * (body->mass * node->mass)/dist_squared;
    double dist = sqrt(dist_squared);
    unit_vec_x = (body->x - node->com_x)/dist;
    unit_vec_y = (body->y - node->com_y)/dist;

    body->force_x += force_scalar * unit_vec_x;
    body->force_y += force_scalar * unit_vec_y;
}

void CompForce(struct Body* body, struct Node* node){
    if (!node->is_empty){ // Reached leaf
        // Direct calculation
        UpdateForceOnBodyByBody(body, node->body);
    } else if (node->is_parent){
        // Check if can use approximation
        double r = Dist(node->com_x, body->x, node->com_y, body->y);
        double d = node->side;
        if (d/r < THETA) {
            // Approximation
            UpdateForceOnBodyByNode(body, node);
        } else {
            for (int i = 0; i<4; i++){
                CompForce(body, node->child_nodes[i]); // Efficient?
            }
        }
    } else { // Node has no body or child nodes
        // Do nothing?
    }
}
