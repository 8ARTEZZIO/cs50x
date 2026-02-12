#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void reset_preferences(void);
int margin(int index);
bool cycle_found(int winner, int loser);
bool not_incoming_edges(int pair_ind);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // check it the name exists in the candidates names
    // if exists then find it's index
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            // add a names index to the #ranks array
            // printf("%s %i\n", name, i);
            ranks[rank] = i;
            return true;
        }
    }
    // if no match - return false
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // for each ranks iteration add it to the preferences array
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // printf("%s [i:%i] over %s [j:%i]\n", candidates[ranks[i]], i, candidates[ranks[j]],
            // j); debugging print printf("%i %i\n", ranks[i], ranks[j]);
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // INITIALIZE DEFAULT VALUES
    for (int m = 0; m < (MAX * (MAX - 1) / 2); m++)
    {
        pairs[m].winner = -1;
        pairs[m].loser = -1;
    }

    // iterate preferences
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {

            // if preferences[i][j] > preferences[j][i]
            if (preferences[i][j] > preferences[j][i])
            {
                printf("%s: %i %s: %i\n", candidates[i], preferences[i][j], candidates[j],
                       preferences[j][i]);
                // then it's a winner on the [i] side
                pairs[pair_count].winner = i;
                // and a loser on a [j] side
                pairs[pair_count].loser = j;
                // increment pair_count by one
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{

    for (int m = 0; m < pair_count - 1; m++)
    {
        // assume the current position holds
        // the highest nr
        int max_indx = m;

        for (int n = m + 1; n < pair_count; n++)
        {
            // selection sort algorithm
            if (margin(n) > margin(max_indx))
            {
                max_indx = n;
            }
        }

        // swap elements
        int temp1 = pairs[max_indx].winner;
        int temp2 = pairs[max_indx].loser;
        pairs[max_indx].winner = pairs[m].winner;
        pairs[max_indx].loser = pairs[m].loser;
        pairs[m].winner = temp1;
        pairs[m].loser = temp2;
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int m = 0; m < candidate_count; m++)
    {
        int i = pairs[m].winner;
        int j = pairs[m].loser;

        // lock the pair 0
        if (m == 0)
        {
            locked[i][j] = true;
        }
        else
        {
            // base case
            if (cycle_found(i, j))
            {
                printf("Cycle Found: %i -> %i\n", i, j);
                locked[i][j] = false;
            }
            // recursice case
            // if there's no cycle found from the current pair
            else
            {
                printf("Locking edge: %i -> %i\n", i, j);
                locked[i][j] = true;
            }
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    // iterate over the pairs where
    // !! M IS THE PAIR INDEX !!
    for (int m = 0; m < candidate_count; m++)
    {

        if (not_incoming_edges(m))
        {
            // if there exist any locked[loser][winner]
            // for the current locked[winner][loser]
            // then skip it
            // the pair that is left is a winner
            printf("%s\n", candidates[m]);
            return;
        }
    }
}

// calculate margin
int margin(int index)
{
    int i = pairs[index].winner;
    int j = pairs[index].loser;

    int margin = preferences[i][j] - preferences[j][i];

    return margin;
}

// Find existing cycle
// return true is the cycle found
bool cycle_found(int winner, int loser)
{
    // base case
    if (loser == winner)
    {
        return true;
    }
    // recursive case
    for (int next = 0; next < pair_count; next++)
    {
        if (locked[loser][next])
        {
            if (cycle_found(winner, next))
            {
                return true;
            }
        }
    }
    return false;
}

// find the lack of incoming edges
bool not_incoming_edges(int pair_ind)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][pair_ind])
        {
            return false;
        }
    }
    return true;
}
