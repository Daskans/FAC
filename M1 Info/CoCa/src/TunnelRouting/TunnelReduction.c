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
 * @param operation the operation
 * @param length The length of the sought path.
 * @param pos the position in the stack
 * @return Z3_ast
 */
Z3_ast operation_is_correct(Z3_context ctx,TunnelNetwork network, stack_action operation, int length, int pos)
{
    int height_change[10] = {0, 0, 1, 1, 1, 1, -1, -1, -1, -1}; // je suis trop smart
    int height_upper_limit[10] = {0, 0, 1, 1, 1, 1, 0, 0, 0, 0};
    int height_lower_limit[10] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1};

    int num_node = tn_get_num_nodes(network);
    int stack_size = get_stack_size(length);

    int h_min = height_lower_limit[operation];
    int h_max = stack_size - height_upper_limit[operation] - 1;
    int h_size = h_max - h_min + 1;

    if (h_min > h_max || pos == 0) {
        return Z3_mk_false(ctx);
    }

    Z3_ast all_nodes[num_node]; // OR[u]

    if (pos > 0) {
        for (int u_node = 0; u_node < num_node; u_node ++) { // receiver
            if (tn_node_has_action(network, u_node, operation)) {
                Z3_ast all_other_nodes[num_node]; // OR[(u,v)eE]
                for (int v_node = 0; v_node < num_node; v_node++) { // sender
                    if (tn_is_edge(network, v_node, u_node)) {
                        Z3_ast all_height[h_size]; // OR[0=<k=<hmax]
                        for (int k = h_min; k <= h_max; k++) {
                            Z3_ast neighbor_check[4]; // Xu, Xv, Hi-1(hi-1), Hi(hi) or Hi-1(i-1 - 1)

                            int ku = k + height_change[operation];
                            int kv = k;

                            neighbor_check[0] = tn_path_variable(ctx, u_node, pos, ku); // Xu,i,k+change
                            neighbor_check[1] = tn_path_variable(ctx, v_node, pos - 1, kv); // Xv,i-1,k

                            if (operation == transmit_4 || operation == push_4_4 || operation == push_4_6 || operation == pop_4_4 || operation == pop_6_4) {
                                neighbor_check[2] = tn_4_variable(ctx, pos - 1, kv); // Hi-1(hi-1) = 4
                            } else {
                                neighbor_check[2] = tn_6_variable(ctx, pos - 1, kv); // Hi-1(hi-1) = 6
                            }

                            if (operation <= transmit_6) {
                                neighbor_check[3] = Z3_mk_true(ctx);
                            } else if (operation == push_4_4 || operation == push_6_4) {
                                neighbor_check[3] = tn_4_variable(ctx, pos, ku); // Hi(hi) = 4
                            } else if (operation == push_4_6 || operation == push_6_6) {
                                neighbor_check[3] = tn_6_variable(ctx, pos, ku); // Hi(hi) = 6
                            }  else if (operation == pop_4_4 || operation == pop_4_6) {
                                neighbor_check[3] = tn_4_variable(ctx, pos - 1, kv - 1); // Hi-1(i-1 - 1) = 4
                            } else if (operation == pop_6_4 || operation == pop_6_6) {
                                neighbor_check[3] = tn_6_variable(ctx, pos - 1, kv - 1); // Hi-1(i-1 - 1) = 6
                            }

                            all_height[k - h_min] = Z3_mk_and(ctx, 4, neighbor_check); // (Xu,i,k+change and Xv,i-1,k and Hi-1(hi-1) and (Hi(hi) or Hi-1(i-1 - 1)))
                        }
                        all_other_nodes[v_node] = Z3_mk_or(ctx, h_size, all_height); // OR[0=<k=<hmax] (Xu,i,k+change and Xv,i-1,k and Hi-1(hi-1) and (Hi(hi) or Hi-1(i-1 - 1)))
                    } else {
                        all_other_nodes[v_node] = Z3_mk_false(ctx);
                    }
                }
                all_nodes[u_node] = Z3_mk_or(ctx, num_node, all_other_nodes); // OR[v] ( OR[0=<k=<hmax] (Xu,i,k+change and Xv,i-1,k and Hi-1(hi-1) and (Hi(hi) or Hi-1(i-1 - 1))) )
            } else {
                all_nodes[u_node] = Z3_mk_false(ctx);
            }
        }
    }
    Z3_ast transmit_conditions = Z3_mk_or(ctx, num_node, all_nodes); // OR[(u,v)eE] ( OR[0=<k=<hmax] (Xu,i,k+change and Xv,i-1,k and Hi-1(hi-1) and (Hi(hi) or Hi-1(i-1 - 1))) )
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
 * @param length la longueur du chemin actuel
 * @return Z3_ast
 */
Z3_ast operations_conditions(Z3_context ctx, TunnelNetwork network, int length)
{
    Z3_ast conditions[length];
    for (int pos = 0; pos < length; pos ++) {
        Z3_ast all_operation[10];
        for (int op = 0; op < NumActions; op++) {
            all_operation[op] = transmit_is_correct(ctx, network, (stack_action)op, length, pos);
        }
        conditions[length] = Z3_mk_or(ctx, 10, all_operation);
    }
    return Z3_mk_and(ctx, length, conditions);
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

/**
 * @brief the formula stating that the path is a valid path
 *
 * @param ctx the solver context
 * @param network the network
 * @param length the total length of the system
 * @return Z3_ast
 */
Z3_ast tn_reduction(Z3_context ctx, const TunnelNetwork network, int length)
{
    Z3_ast formula[length];
    for (int g = 1; g <= length; g++) {
        Z3_ast path_conditions[4];
        path_conditions[0] = is_a_path(ctx);
        path_conditions[1] = initial_node_conditions(ctx, network);
        path_conditions[2] = final_node_conditions(ctx, network, g);
        path_conditions[3] = operations_conditions(ctx, network, g);
        formula[g - 1] = Z3_mk_and(ctx, 4, path_conditions);
    }
    return Z3_mk_or(ctx, length, formula);
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