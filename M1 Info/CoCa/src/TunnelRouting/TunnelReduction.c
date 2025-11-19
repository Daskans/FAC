#include "TunnelReduction.h"
#include "Z3Tools.h"
#include "stdio.h"

/**
 * @brief Creates the variable "x_{node,pos,stack_height}" of the reduction (described in the subject).
 *
 * @param ctx The solver context.
 * @param node A node.
 * @param pos The path position.
 * @param stack_height The highest cell occupied of the stack at that position.
 * @return Z3_ast
 */
Z3_ast tn_path_variable(Z3_context ctx, int node, int pos, int stack_height)
{
    char name[60];
    snprintf(name, 60, "node %d,pos %d, height %d", node, pos, stack_height);
    return mk_bool_var(ctx, name);
}

/**
 * @brief Creates the variable "y_{pos,height,4}" of the reduction (described in the subject).
 *
 * @param ctx The solver context.
 * @param pos The path position.
 * @param height The height of the cell described.
 * @return Z3_ast
 */
Z3_ast tn_4_variable(Z3_context ctx, int pos, int height)
{
    char name[60];
    snprintf(name, 60, "4 at height %d on pos %d", height, pos);
    return mk_bool_var(ctx, name);
}

/**
 * @brief Creates the variable "y_{pos,height,6}" of the reduction (described in the subject).
 *
 * @param ctx The solver context.
 * @param pos The path position.
 * @param height The height of the cell described.
 * @return Z3_ast
 */
Z3_ast tn_6_variable(Z3_context ctx, int pos, int height)
{
    char name[60];
    snprintf(name, 60, "6 at height %d on pos %d", height, pos);
    return mk_bool_var(ctx, name);
}

/**
 * @brief Create the formula stating that each node has exaclty one height
 *
 * @param ctx the solver context
 * @param num_node the number of node in the network
 * @param length The length of the sought path.
 * @return Z3_ast
 */
Z3_ast each_node_has_one_height(Z3_context ctx, int num_node, int length)
{
    int stack_size = get_stack_size(length);
    Z3_ast all_nodes[length * num_node];
    for (int node = 0; node < num_node; node++) {
        for (int pos = 0; pos < length; pos++) {
            Z3_ast h_diff[stack_size];
            for (int h = 0; h < stack_size; h++) {
                h_diff[h] = tn_path_variable(ctx, node, pos, h);
            }
            all_nodes[(node * num_node) + pos] = uniqueFormula(ctx, h_diff, stack_size);
        }
    }
    return Z3_mk_and(ctx, length * num_node, all_nodes);
}

/**
 * @brief create the formula stating that the path needs to be simple
 *
 * @param ctx the solver context
 * @param pos The path position.
 * @param height The height of the cell described.
 * @return Z3_ast
 */
Z3_ast simple_path(Z3_context ctx, int num_node, int length)
{

}

/**
 * @brief Create the formula stating that the stack height at the first node has to be 0 and that
 * the first operation has to be an ipv4 transfer
 *
 * @param ctx the solver context
 * @param network the network
 * @param height the height of the cell described
 * @return Z3_ast
 */
Z3_ast initial_node_conditions(Z3_context ctx, const TunnelNetwork network)
{
    Z3_ast formula[3];
    int initial_node = tn_get_initial(network);
    formula[0] = tn_path_variable(ctx, initial_node, 0, 0); // h(Xs) = 0
    formula[1] = tn_4_variable(ctx, 0, 0); // s = IPv4
    int num_node = tn_get_num_nodes(network);
    Z3_ast all_node[num_node];
    for (int node = 0; node < num_node; node++) {
        all_node[node] = tn_4_variable(ctx, 1, 0);
    }
    formula[2] = Z3_mk_or(ctx, num_node, all_node);
    return Z3_mk_and(ctx, 3, formula);
}

/**
 * @brief Create the formula stating that the stack height at the final node has to be 0
 *
 * @param ctx the solver context
 * @param network the network
 * @param height the height of the cell described
 * @return Z3_ast
 */
Z3_ast final_node_conditions(Z3_context ctx, const TunnelNetwork network, int path_length)
{
    int final_node = tn_get_final(network);
    int last_pos = path_length;
    Z3_ast formula = tn_path_variable(ctx, final_node, 0, path_length);
    return formula;
}

/**
 * @brief the formula stating that transmit is valid
 *
 * @param ctx the solver context
 * @param node A node.
 * @param network the network
 * @param operation either transmit_4 or transmit_6
 * @param length The length of the sought path.
 * @param pos the position in the stack
 * @return Z3_ast
 */
Z3_ast transmit_is_correct(Z3_context ctx,TunnelNetwork network, stack_action operation, int length, int pos)
{
    int num_node = tn_get_num_nodes(network);
    int stack_size = get_stack_size(length);
    Z3_ast all_nodes[num_node]; // OR[u]
    if (pos > 0) {

        for (int node = 0; node < num_node; node ++) {

            if (tn_node_has_action(network, node, operation)) {

                Z3_ast all_other_nodes[num_node]; // OR[(u,v)eE]

                for (int new_node = 0; new_node < num_node; new_node++) {

                    if (tn_is_edge(network, node, new_node)) {

                        Z3_ast all_height[stack_size]; // OR[0=<k=<hmax]

                        for (int k = 0; k < stack_size; k++) {

                            Z3_ast neighbor_check[3]; // Xu, Xv, Hi-1(hi-1)

                            neighbor_check[0] = tn_path_variable(ctx, node, pos, k); // Xu,i,k
                            neighbor_check[1] = tn_path_variable(ctx, new_node, pos-1, k); // Xv,i-1,k

                            if (operation == transmit_4) {
                                neighbor_check[2] = tn_4_variable(ctx, pos - 1, k); // Hi-1(hi-1) = 4
                            } else {
                                neighbor_check[2] = tn_6_variable(ctx, pos - 1, k); // Hi-1(hi-1) = 6
                            }

                            all_height[k] = Z3_mk_and(ctx, 3, neighbor_check); // (Xu,i,k and Xv,i-1,k and Hi-1(hi-1))
                        }
                        all_other_nodes[new_node] = Z3_mk_or(ctx, stack_size, all_height); // OR[0=<k=<hmax] (Xu,i,k and Xv,i-1,k and Hi-1(hi-1))
                    } else {
                        all_other_nodes[new_node] = Z3_mk_false(ctx);
                    }
                }
                all_nodes[node] = Z3_mk_or(ctx, num_node, all_other_nodes); // OR[veE] ( OR[0=<k=<hmax] (Xu,i,k and Xv,i-1,k and Hi-1(hi-1)) )
            } else {
                all_nodes[node] = Z3_mk_false(ctx);
            }
        }
    }
    Z3_ast transmit_conditions = Z3_mk_or(ctx, num_node, all_nodes); // OR[ueE] ( OR[veE] (OR[0=<k=<hmax] (Xu,i,k and Xv,i-1,k and Hi-1(hi-1))) )
    return transmit_conditions;
}

/**
 * @brief the formula stating that the path is indead a path
 *
 * @param ctx the solver context
 * @return Z3_ast
 */
Z3_ast is_a_path(Z3_context ctx)
{
}

/**
 * @brief the formula stating that each operations needs to be correct
 *
 * @param ctx the solver context
 * @param network the network
 * @param operation the operation (transfer_4_4, transfer_6_6, push_4_6, etc...)
 * @return Z3_ast
 */
Z3_ast operations_conditions(Z3_context ctx, TunnelNetwork network, int length)
{
    Z3_ast conditions[10];
    for (int pos = 0; pos < length; pos ++) {
        conditions[0] = transmit_is_correct(ctx, network, transmit_4, length, pos);
        conditions[1] = transmit_is_correct(ctx, network, transmit_6, length, pos);
        conditions[2] = push_is_correct(ctx, network, push_4_4, length, pos);
        conditions[3] = push_is_correct(ctx, network, push_4_6, length, pos);
        conditions[4] = push_is_correct(ctx, network, push_6_4, length, pos);
        conditions[5] = push_is_correct(ctx, network, push_6_6, length, pos);
        conditions[6] = pop_is_correct(ctx, network, pop_4_4, length, pos);
        conditions[7] = pop_is_correct(ctx, network, pop_4_6, length, pos);
        conditions[8] = pop_is_correct(ctx, network, pop_6_4, length, pos);
        conditions[9] = pop_is_correct(ctx, network, pop_6_6, length, pos);
    }
    return Z3_mk_or(ctx, 10, conditions);
}

/**
 * @brief the formula stating that the path is a valid path
 *
 * @param ctx the solver context
 * @param network the network
 * @return Z3_ast
 */
Z3_ast valid_path(Z3_context ctx, const TunnelNetwork network)
{
    Z3_ast formula[4];
    formula[0] = is_a_path(ctx);
    formula[1] = initial_node_conditions(ctx, network);
    formula[2] = final_node_condidtions(ctx, network, NULL);
    formula[3] = operations_conditions(ctx, network);
    return Z3_mk_and(ctx, 4, formula);
}

/**
 * @brief Wrapper to have the correct size of the array representing the stack (correct cells of the stack will be from 0 to (get_stack_size(length)-1)).
 *
 * @param length The length of the sought path.
 * @return int
 */
int get_stack_size(int length)
{
    return length / 2 + 1;
}

Z3_ast tn_reduction(Z3_context ctx, const TunnelNetwork network, int length)
{
    return Z3_mk_false(ctx);
}

void tn_get_path_from_model(Z3_context ctx, Z3_model model, TunnelNetwork network, int bound, tn_step *path)
{
    int num_nodes = tn_get_num_nodes(network);
    int stack_size = get_stack_size(bound);
    for (int pos = 0; pos < bound; pos++)
    {
        int src = -1;
        int src_height = -1;
        int tgt = -1;
        int tgt_height = -1;
        for (int n = 0; n < num_nodes; n++)
        {
            for (int height = 0; height < stack_size; height++)
            {
                if (value_of_var_in_model(ctx, model, tn_path_variable(ctx, n, pos, height)))
                {
                    src = n;
                    src_height = height;
                }
                if (value_of_var_in_model(ctx, model, tn_path_variable(ctx, n, pos + 1, height)))
                {
                    tgt = n;
                    tgt_height = height;
                }
            }
        }
        int action = 0;
        if (src_height == tgt_height)
        {
            if (value_of_var_in_model(ctx, model, tn_4_variable(ctx, pos, src_height)))
                action = transmit_4;
            else
                action = transmit_6;
        }
        else if (src_height == tgt_height - 1)
        {
            if (value_of_var_in_model(ctx, model, tn_4_variable(ctx, pos, src_height)))
            {
                if (value_of_var_in_model(ctx, model, tn_4_variable(ctx, pos + 1, tgt_height)))
                    action = push_4_4;
                else
                    action = push_4_6;
            }
            else if (value_of_var_in_model(ctx, model, tn_4_variable(ctx, pos + 1, tgt_height)))
                action = push_6_4;
            else
                action = push_6_6;
        }
        else if (src_height == tgt_height + 1)
        {
            {
                if (value_of_var_in_model(ctx, model, tn_4_variable(ctx, pos, src_height)))
                {
                    if (value_of_var_in_model(ctx, model, tn_4_variable(ctx, pos + 1, tgt_height)))
                        action = pop_4_4;
                    else
                        action = pop_6_4;
                }
                else if (value_of_var_in_model(ctx, model, tn_4_variable(ctx, pos + 1, tgt_height)))
                    action = pop_4_6;
                else
                    action = pop_6_6;
            }
        }
        path[pos] = tn_step_create(action, src, tgt);
    }
}

void tn_print_model(Z3_context ctx, Z3_model model, TunnelNetwork network, int bound)
{
    int num_nodes = tn_get_num_nodes(network);
    int stack_size = get_stack_size(bound);
    for (int pos = 0; pos < bound + 1; pos++)
    {
        printf("At pos %d:\nState: ", pos);
        int num_seen = 0;
        for (int node = 0; node < num_nodes; node++)
        {
            for (int height = 0; height < stack_size; height++)
            {
                if (value_of_var_in_model(ctx, model, tn_path_variable(ctx, node, pos, height)))
                {
                    printf("(%s,%d) ", tn_get_node_name(network, node), height);
                    num_seen++;
                }
            }
        }
        if (num_seen == 0)
            printf("No node at that position !\n");
        else
            printf("\n");
        if (num_seen > 1)
            printf("Several pair node,height!\n");
        printf("Stack: ");
        bool misdefined = false;
        bool above_top = false;
        for (int height = 0; height < stack_size; height++)
        {
            if (value_of_var_in_model(ctx, model, tn_4_variable(ctx, pos, height)))
            {
                if (value_of_var_in_model(ctx, model, tn_6_variable(ctx, pos, height)))
                {
                    printf("|X");
                    misdefined = true;
                }
                else
                {
                    printf("|4");
                    if (above_top)
                        misdefined = true;
                }
            }
            else if (value_of_var_in_model(ctx, model, tn_6_variable(ctx, pos, height)))
            {
                printf("|6");
                if (above_top)
                    misdefined = true;
            }
            else
            {
                printf("| ");
                above_top = true;
            }
        }
        printf("\n");
        if (misdefined)
            printf("Warning: ill-defined stack\n");
    }
    return;
}