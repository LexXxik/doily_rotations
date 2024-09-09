#include <string.h>

#include "doily.c"
#include "generation.c"
#include "hashtable.c"

bv TRICENTRIC_TRIAD[] = { XY, ZY, YI };

        int results[DOILY_SIZE][DOILY_SIZE][DOILY_SIZE][DOILY_SIZE][DOILY_SIZE][DOILY_SIZE][2][13] = { 0 };
//                         ^          ^           ^           ^            ^          ^     ^   ^
// type of Observable:     A          B           C           D            E          F     |   |
//                                                           Linear (0), or quadratic (1)-\_|   |
//             Configuration of negative lines + 1 so that indexing coincides with cathegory -\_|
//  ***********
// NOTE:
//Negative line configurations corresponding to 7B and 8B are stored at indices 1, and 2 respectively

bool categorize_doily(bv doily[]);

/**
 * @brief Creates a waffled 2-6 doily, and then rotates each layer to determine whether resulting doily is contextual 
 * 
 */
void main_procedure()
{
    bool repeated_doily = false; // doily where at least two subdoilies are the same

    int rep_contextual = 0;
    int rep_non_contextual = 0;
    int contextual = 0;
    int non_contextual = 0;
    int duplicate_count = 0;

    // First three loops create every possible combination of doily waffle
    for(size_t i = 0; i < N_CONSTANT_DOILIES; i++)
    {
        for(size_t j = 0; j < N_CONSTANT_DOILIES; j++)
        {
            for(size_t k = 0; k < N_CONSTANT_DOILIES; k++)
            {
                if(i == j || i == k || k == i)
                    repeated_doily = true;
                
                bv built_doily[DOILY_SIZE];

                doily_wafler_2_6(built_doily, CONSTANT_DOILIES[i], CONSTANT_DOILIES[j], CONSTANT_DOILIES[k]);

                // These three loops ensure that each doily wafle is rotated in its subdoilies
                for(size_t l = 0; l < N_GROUPED_VERTICES; l++)
                {
                    for(size_t m = 0; m < N_GROUPED_VERTICES; m++)
                    {
                        for(size_t n = 0; n < N_GROUPED_VERTICES; n++)
                        {
                            if(is_contextual(built_doily))
                            {
                                bv root[OVOID_COUNT+1] = {0,0,0,0,0,0};
                                get_doily_root(built_doily, root);
                                if(!is_duplicate(root))
                                {
                                    insert(root);
                                    if(!categorize_doily(built_doily))
                                        print("ERROR: Caegorization failed!\n");
                                }
                                else
                                {
                                    //print("duplicate\n");
                                    duplicate_count++;
                                }
                                if(repeated_doily)
                                    rep_contextual++;
                                else
                                    contextual++;
                            }
                            else
                            {
                                if(repeated_doily)
                                    rep_non_contextual++;
                                else
                                    non_contextual++;
                            }
                            rotate_sub_doily(built_doily, 4);
                        }
                        rotate_sub_doily(built_doily, 2);
                    }
                    if(l != 4)
                        rotate_sub_doily(built_doily, 0);
                }
                repeated_doily = false;
            }
        }
    }
    print("\n\n*** NON-REPEATED ***\n");
    print("contextual: %d\n", contextual);
    print("non-contextual: %d\n\n", non_contextual);

    print("*** REPEATED ***\n");
    print("contextual: %d\n", rep_contextual);
    print("non-contextual: %d\n", rep_non_contextual);

    print("\n\n NUMBER OF DUPLICATES %d!\n", duplicate_count);
}

/**
 * @brief NON-publishable: Counts number of observables of each type in the doily
 * 
 * @param doily 
 * @param A type of observable (N_OBS-1 = 5 Is)
 * @param B type of observable (N_OBS-2 = 4 Is)
 * @param C type of observable (N_OBS-3 = 3 Is)
 * @param D type of observable (N_OBS-4 = 2 Is)
 * @param E type of observable (N_OBS-5 = 1 Is)
 * @param F type of observable (N_OBS-6 = 0 Is)
 * @return true 
 * @return false 
 */
bool count_n_Is(bv doily[], int *A, int *B, int *C, int *D, int *E, int *F)
{
    return true;
}

/**
 * @brief NON-publishable: Determines whether given doily is quadratic or linear 
 * 
 * @param doily 
 * @return true 
 * @return false 
 */
bool is_quadratic(bv doily[])
{
    return true
}

/**
 * @brief NON-publishable: Counts the number of negative lines and hence determines corresponding configuration (return and index for result[][][][][][][][])
 * NOTE: 7B, 8B are stored at indices 1 and 2 respectively.
 * 
 * @param doily 
 * @return size_t 
 */
size_t count_negative_lines(bv doily[])
{
    return 13;    
}

/**
 * @brief NON-publishable: Categorizes doily according to linearity, number of observables of each type, and configuration of negativel lines, 
 *         then it makes a record to result array
 * 
 * @param doily 
 * @return true 
 * @return false 
 */
bool categorize_doily(bv doily[])
{
    return true;
}

void print_results()
{
    // **** BLOC 1 ****
    // **** Specifying row ****
    //First 6 loops go through types A, B, C etc. of observables
    print("| A | B | C | D | E | F | v | 3 | 4 | 5 | 6 | 7A | 7B| 8A | 8B | 9 | 10 | 11 | 12 |\n");
    print("-----------------------------------------------------------------------------------\n");
    for(size_t a = 0; a < DOILY_SIZE; a++)
    {
        for(size_t b = 0; b < DOILY_SIZE; b++)
        {
            for(size_t c = 0; c < DOILY_SIZE; c++)
            {
                for(size_t d = 0; d < DOILY_SIZE; d++)
                {
                    for(size_t e = 0; e < DOILY_SIZE; e++)
                    {
                        for(size_t f = 0; f < DOILY_SIZE; f++)
                        {
                            //Quadratic, or Linear?
                            for(size_t q = 0; q < 2; q++)
                            {
                                // **** BLOC 2 ****
                                // **** Specifying column ****
                                /*if((a+b+c+d+e+f) != 15)
                                    continue;*/
                                bool empty_row = true;
                                for(size_t negative_line = 3; negative_line < 13; negative_line++)
                                {
                                    int result = results[a][b][c][d][e][f][q][negative_line];
                                    //print("%zu, %zu, %zu, %zu, %zu, %zu, %zu| %zu ---- %d \n", a, b, c, d, e, f, q, negative_line, result);
                                    if (result != 0)
                                    {
                                        empty_row = false;
                                        break;
                                    }
                                    // 7B
                                    if(negative_line == 7)
                                    {
                                        result = results[a][b][c][d][e][f][q][1];
                                    }
                                    // 8B
                                    if (negative_line == 8)
                                    {
                                        result = results[a][b][c][d][e][f][q][2];
                                    }
                                    if (result != 0)
                                    {
                                        empty_row = false;
                                        break;
                                    }
                                }

                                if(!empty_row)
                                {
                                    print("| %zu |", a);
                                    print(" %zu |", b);
                                    print(" %zu |", c);
                                    print(" %zu |", d);
                                    print(" %zu |", e);
                                    print(" %zu |", f);
                                    print(" %zu |", q);
                                    for(size_t negative_line = 3; negative_line < 13; negative_line++)
                                    {
                                        int result = results[a][b][c][d][e][f][q][negative_line];
                                        if(result == 0)
                                        {
                                            print("   |");
                                        }
                                        if(result != 0)
                                            print(" %d |", result);

                                        if(negative_line == 7)
                                        {
                                            result = results[a][b][c][d][e][f][q][1];
                                            if(result == 0)
                                            {
                                                print("   |");
                                            }
                                            if(result != 0)
                                                print(" %d |", result);
                                        }
                                        // 8B
                                        if (negative_line == 8)
                                        {
                                            result = results[a][b][c][d][e][f][q][2];
                                            if(result == 0)
                                            {
                                                print("   |");
                                            }
                                            if(result != 0)
                                                print(" %d |", result);
                                        }
                                        if(negative_line == 12)
                                        print("\n");
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    //print("\n %d \n", results[0][0][2][4][4][5][0][3]);
}

/**
 * @brief wrapping function for all functions that need to be executed befor the main_procedure() 
 * 
 */
void inicialization_procedure()
{
    generate_negative();
    build_constant_doilies();
    populate_doily_lines();
}

int main(int argc, char *argv[])
{
    inicialization_procedure();

    bv built_doily[DOILY_SIZE];

    doily_wafler_2_6(built_doily, CONSTANT_DOILIES[0], CONSTANT_DOILIES[1], CONSTANT_DOILIES[2]);
    bv doily_root[OVOID_COUNT + 1] = {};

    
    main_procedure();
    print_results();
}