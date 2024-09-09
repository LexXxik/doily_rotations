/**
 * @file doily.c
 * @author Adrian Bartko
 * @brief used for auxiliary functions to create doily waffles for rotation problem
 * 
 */
#include "bv.c"
#include "complex.c"
#include "constants.c"
#include "constant_doilies.c"

void populate_ovoid(bv doily[], bv ovoid[], size_t default_ovoid_index);
void sort_ovoid(bv ovoid[]);

/**
 * @brief defines lines of DOILY_LINES array
 * 
 */
void populate_doily_lines()
{
    for(size_t i =  0; i < N_GROUPED_VERTICES; i++)
    {
        // to populate lines forming the pentagon
        DOILY_LINES[i][0] = OUTER_VERTICES[i];
        DOILY_LINES[i][1] = MID_EDGE_VERTICES[i];
        DOILY_LINES[i][2] = OUTER_VERTICES[(i+1) % N_GROUPED_VERTICES];

        //to populate lines interesecting each other
        DOILY_LINES[i+5][0] = OUTER_VERTICES[i];
        DOILY_LINES[i+5][1] = INNER_VERTICES[(i+2) % N_GROUPED_VERTICES];
        DOILY_LINES[i+5][2] = MID_EDGE_VERTICES[(i+2) % N_GROUPED_VERTICES];

        //to populate curved lines
        DOILY_LINES[i+10][0] = INNER_VERTICES[(i+4) % N_GROUPED_VERTICES];
        DOILY_LINES[i+10][1] = MID_EDGE_VERTICES[i];
        DOILY_LINES[i+10][2] = INNER_VERTICES[(i+1) % N_GROUPED_VERTICES];
    }
}

/**
 * @brief prints array DOILY_LINES to verify that hardcode is correct 
 * 
 */
void print_doily_lines()
{
    for(size_t i = 0; i < N_LINES; i++)
    {
        print("{");
        print_BV_custom(DOILY_LINES[i][0], 2);
        print_BV_custom(DOILY_LINES[i][1], 2);
        print_BV_custom(DOILY_LINES[i][2], 2);
        print("}");
        print("\n");
        if(i == 4 || i == 9)
            print("\n");
    }

}

/**
 * @brief given an empty array and set of inner, mid, and outer vertices it populates some_doily
 * 
 * @param some_doily 
 * @param outer_vertices 
 * @param mid_vertices 
 * @param inner_vertices 
 */
void doily_builder(bv some_doily[], bv outer_vertices[], bv mid_vertices[], bv inner_vertices[])
{
    for(size_t i = 0; i < N_GROUPED_VERTICES; i++)
    {
        some_doily[OUTER_VERTICES[i]] = outer_vertices[i];
        some_doily[MID_EDGE_VERTICES[i]] = mid_vertices[i];
        some_doily[INNER_VERTICES[i]] = inner_vertices[i];
    }
    //
    some_doily[0] = 0;
}

/**
 * @brief Utilizes doily_builder to generate 4 constant doilies
 * 
 */
void build_constant_doilies()
{
    doily_builder(INDEX_DOILY, OUTER_VERTICES, MID_EDGE_VERTICES, INNER_VERTICES);
    doily_builder(CONSTANT_DOILIES[ALPHA], ALPHA_OUTER, ALPHA_MID, ALPHA_INNER);
    doily_builder(CONSTANT_DOILIES[BETA], BETA_OUTER, BETA_MID, BETA_INNER);
    doily_builder(CONSTANT_DOILIES[GAMMA], GAMMA_OUTER, GAMMA_MID, GAMMA_INNER);
    doily_builder(CONSTANT_DOILIES[DELTA], DELTA_OUTER, DELTA_MID, DELTA_INNER);
}

/**
 * @brief Take three 2-qubit doilies a, b, and c and stacks them on top waffles them together to form 6 qubit doily
 * 
 * @param doily_6 
 * @param a_doily_2 
 * @param b_doily_2 
 * @param c_doily_2 
 */
void doily_wafler_2_6(bv doily_6[], bv a_doily_2[], bv b_doily_2[], bv c_doily_2[])
{
    for(size_t i = 0; i < DOILY_SIZE; i++)
    {
        bv combined_gate = 0;
        for(size_t j = 0; j < 2; j++)
            combined_gate = set_gate(combined_gate, get_gate(a_doily_2[i], j, 2), j);
        /*print_BV_custom(a_doily_2[i], 2);
        print("-------> ")
        print_BV_custom(combined_gate)*/

        for(size_t j = 0; j < 2; j++)
            combined_gate = set_gate(combined_gate, get_gate(b_doily_2[i], j, 2), j + 2);

        for(size_t j = 0; j < 2; j++)
            combined_gate = set_gate(combined_gate, get_gate(c_doily_2[i], j, 2), j + 4);

        doily_6[i] = combined_gate;        
    }
}

/**
 * @brief prints doily to the console give its qubit cardinality
 * 
 * @param doily 
 * @param n_obs 
 */
void print_doiy(bv doily[], size_t n_obs)
{
    for(size_t i = 0; i < N_LINES; i++)
    {
        if(i == 0)
            print("\n *** Pentagon Lines ***\n");
        if(i == 5)
            print("\n *** Intersecting Lines ***\n");
        if(i == 10)
            print("\n *** Curved Lines *** \n");
        for(size_t j = 0; j < NB_POINTS_PER_LINE; j++)
        {
            print_BV_custom(doily[DOILY_LINES[i][j]], n_obs);
        }
        print("\n");

    }
}

/**
 * @brief Subroutine of rotate_subdoily: for a given vertex pool rotates subdoily indices by one (think of cycle notation of permutations);
 * 
 * @param the_doily 
 * @param VERTEX_POOL 
 * @param ind_rot_gate 
 */
void rotate_subroutine(bv the_doily[], bv VERTEX_POOL[], unsigned int ind_rot_gate)
{
        bv saved_obs = 0;
    for(size_t i = 0; i < N_GROUPED_VERTICES; i++)
    {
        bv *target = &the_doily[VERTEX_POOL[(i+1)%N_GROUPED_VERTICES]];
        bv rotating_obs = 0;
        if(i == 0)
            rotating_obs = get_gates(the_doily[VERTEX_POOL[i]], ind_rot_gate, N_COMPOSITE_OBS);
        else
            rotating_obs = get_gates(saved_obs, ind_rot_gate, N_COMPOSITE_OBS);
        saved_obs = *target;

        *target = null_gate(*target, ind_rot_gate, N_COMPOSITE_OBS) Qplus rotating_obs;
    }
}

/**
* @brief rotates indexed subdoily by one 
*
* @param the_doily pointer to the doily that will be rotated
* @param ind_rot_gate index of the first gate that will be rotated
*/
void rotate_sub_doily(bv the_doily[], unsigned int ind_rot_gate)
{
    rotate_subroutine(the_doily, OUTER_VERTICES, ind_rot_gate);
    //print("\n");
    rotate_subroutine(the_doily, MID_EDGE_VERTICES, ind_rot_gate);
    //print("\n");
    rotate_subroutine(the_doily, INNER_VERTICES, ind_rot_gate);
}

/**
 * @brief Determines whether 3 observables commute using symplectic polar form
 * 
 * @param obs1 
 * @param obs2 
 * @param obs3 
 * @return true 
 * @return false 
 */
bool is_commuting(bv obs1, bv obs2, bv obs3)
{
    // is 0 only if all inner products evaluate to 0 - all pairs commute
    if((innerProduct(obs1, obs2) + innerProduct(obs1, obs3) + innerProduct(obs2, obs3)) == 0)
        return true;
    else
        return false;

}

bool is_ovoid(bv ovoid[])
{
    bool found_commuting_pair = false;

    for(size_t i = 0; i < OVOID_COUNT; i++)
    {
        for(size_t j = 0; j < OVOID_COUNT; j++)
        {
            if(i == j)
                continue;
            
            if(innerProduct(ovoid[i], ovoid[j]) == 0)
            {
                found_commuting_pair = true;
                return !found_commuting_pair;
            }
                
        }
    }
    return !found_commuting_pair;
}

/**
 * @brief determines whether the_doily is contextual 
 * 
 * @param the_doily 
 * @return true 
 * @return false 
 */
bool is_contextual(bv the_doily[])
{
    for(size_t i = 0; i < N_LINES; i++)
    {
        if(!is_commuting(the_doily[DOILY_LINES[i][0]], the_doily[DOILY_LINES[i][1]], the_doily[DOILY_LINES[i][2]]))
            return false;   
    }

    for(size_t i = 0; i < OVOID_INDEXES_COUNT; i++)
    {
        bv ovoid[OVOID_COUNT] = {the_doily[DEFAULT_OVOID[i][0]], the_doily[DEFAULT_OVOID[i][1]], 
                                  the_doily[DEFAULT_OVOID[i][2]], the_doily[DEFAULT_OVOID[i][3]], 
                                  the_doily[DEFAULT_OVOID[i][4]]};
        if(!is_ovoid(ovoid))
            return false;
    }
    return true;
}

/**
 * @brief determines whether ovoid_1 is lexicographically smaller than ovoid_2 (For this purpose ovoids have to be sorted first) 
 * 
 * @param ovoid_1 
 * @param ovoid_2 
 * @return true 
 * @return false 
 */
bool is_smaller_ovoid(bv ovoid_1[], bv ovoid_2[])
{
    sort_ovoid(ovoid_1);
    sort_ovoid(ovoid_2);

    for(size_t i = 0; i < OVOID_COUNT; i++)
    {
        if(ovoid_1[i] < ovoid_2[i])
        {
            return true;
        }
        else if(ovoid_1[i] > ovoid_2[i])
        {
            return false;
        }
    }
    return false;
}

/**
 * @brief sorts ovoid by lexicographic order ascending
 * 
 * @param ovoid 
 */
void sort_ovoid(bv ovoid[])
{
    bool pass = false;
    do
    {
        pass = false;
        for(size_t i = 1; i < OVOID_COUNT; i++)
        {
            bv saved = 0;
            if(!(ovoid[i-1] <= ovoid[i]))
            {
                pass = true;
                saved = ovoid[i-1];
                ovoid[i-1] = ovoid[i];
                ovoid[i] = saved;
            }
        }
    } while(pass);
}

/**
 * @brief We are finding center which commutes with first 3 elements of the sorted ovoid, ant anti-commutes with the last two
 * 
 * WARNING - sorted_ovoid[] should be ovoid of the doily[]
 * 
 * @param doily 
 * @param sorted_ovoid 
 * @return size_t 
 */
size_t find_center_index(bv doily[], bv sorted_ovoid[])
{
    //Starting with 1, because at index 0 there is an identity
    size_t center_index = 0;
    for(size_t i = 1; i < DOILY_SIZE; i++)
    {
        //We are looking for an element that commutes (inner product is 0) with first 3 elements of sorted ovoid, and anticommutes with last 2
        // *** NOTE ***
        //Perhaps I can code this using recursion??
        if(innerProduct(doily[i], sorted_ovoid[0]) == 0)
        {
            if(innerProduct(doily[i], sorted_ovoid[1]) == 0)
            {
                if(innerProduct(doily[i], sorted_ovoid[2]) == 0)
                {
                    if(innerProduct(doily[i], sorted_ovoid[3]) == 1)
                    {
                        if(innerProduct(doily[i], sorted_ovoid[4]) == 1)
                        {
                            center_index = i;
                            break;
                        }
                        else
                            continue;
                    }
                    else
                        continue;
                }
                else
                    continue;
            }
            else 
                continue;
        }
        else
            continue;
    }
    return center_index;
}

void print_doily_root(bv doily_root[])
{
    print("\n\n*** OVOID ***\n");
    for(size_t i = 0; i < OVOID_COUNT; i++)
    {
        print_BV_custom(doily_root[i], N_OBS);
        print("\n");
    }
    print("\n *** CENTER *** \n");
    print_BV_custom(doily_root[5], N_OBS);
    print("\n");
}

/**
 * @brief Get the doily root (doily root determines doily) based on the given doily
 * 
 * @param doily 
 * @param doily_root 
 */
void get_doily_root(bv doily[], bv doily_root[])
{
    bv smallest_ovoid[OVOID_COUNT] = {0-1, 0-1, 0-1,0-1, 0-1};
    for(size_t i = 0; i < OVOID_INDEXES_COUNT; i++)
    {
        bv ovoid_1[OVOID_COUNT] = {};

        populate_ovoid(doily, ovoid_1, i);

        if(is_smaller_ovoid(ovoid_1, smallest_ovoid))
        {
            smallest_ovoid[0] = ovoid_1[0];
            smallest_ovoid[1] = ovoid_1[1];
            smallest_ovoid[2] = ovoid_1[2];
            smallest_ovoid[3] = ovoid_1[3];
            smallest_ovoid[4] = ovoid_1[4];
        }
    }

    size_t center_index = find_center_index(doily, smallest_ovoid);

    doily_root[0] = smallest_ovoid[0];
    doily_root[1] = smallest_ovoid[1];
    doily_root[2] = smallest_ovoid[2];
    doily_root[3] = smallest_ovoid[3];
    doily_root[4] = smallest_ovoid[4];
    doily_root[5] = doily[center_index];
}

/**
 * @brief Assigns values to ovoid[] from the doily based on the specified ovoid 
 * 
 * @param doily 
 * @param ovoid 
 * @param default_ovoid_index 
 */
void populate_ovoid(bv doily[], bv ovoid[], size_t default_ovoid_index)
{
    for(size_t i = 0; i < OVOID_COUNT; i++)
    {
        ovoid[i] = doily[DEFAULT_OVOID[default_ovoid_index][i]];
    }
}