/*
    ============================================================================
                                SPOJ - EKO (Eko)
    ============================================================================
    Topic: Binary Search on Answer

    Problem:
    Given the heights of N trees and a required amount of wood M,
    determine the maximum height at which the sawblade can be set so
    that at least M units of wood are collected.

    Approach:
    - Binary Search on the cutting height.
    - For every candidate height, calculate the amount of wood collected.
    - If enough wood is collected, try increasing the cutting height.
    - Otherwise, decrease the cutting height.

    Time Complexity : O(N * log(MaxTreeHeight))
    Space Complexity: O(1)
    ============================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:

    /*
        ------------------------------------------------------------
        Function: canCut()

        Purpose:
        Determines whether setting the sawblade at height 'cut'
        produces at least 'limit' amount of wood.

        Parameters:
            arr   -> Heights of all trees
            cut   -> Current blade height
            limit -> Required amount of wood

        Returns:
            true  -> Enough wood can be collected.
            false -> Collected wood is less than the required amount.
        ------------------------------------------------------------
    */
    bool canCut(vector<long long>& arr, long long cut, long long limit)
    {
        long long collectedWood = 0;

        // Traverse every tree.
        for (auto &tree : arr)
        {
            /*
                Only the portion above the cutting height contributes
                to the collected wood.
            */
            if (tree > cut)
                collectedWood += (tree - cut);

            /*
                Early stopping optimization.

                Once the required amount of wood has been collected,
                there is no need to continue checking the remaining trees.
            */
            if (collectedWood >= limit)
                return true;
        }

        return false;
    }

    /*
        ------------------------------------------------------------
        Function: solveEKO()

        Uses Binary Search on the answer.

        Search Space:
            Minimum blade height = 0
            Maximum blade height = Tallest tree

        Goal:
        Find the highest valid cutting height.
        ------------------------------------------------------------
    */
    long long solveEKO(vector<long long>& arr, long long limit)
    {
        long long low = 0;
        long long high = *max_element(arr.begin(), arr.end());

        // Stores the best valid answer found so far.
        long long answer = 0;

        while (low <= high)
        {
            // Prevent integer overflow.
            long long mid = low + (high - low) / 2;

            /*
                If cutting at 'mid' produces enough wood,
                then this is a valid answer.

                Try increasing the cutting height to maximize it.
            */
            if (canCut(arr, mid, limit))
            {
                answer = mid;
                low = mid + 1;
            }
            /*
                Otherwise, the blade is too high,
                resulting in insufficient wood.

                Lower the blade height.
            */
            else
            {
                high = mid - 1;
            }
        }

        return answer;
    }
};

int main()
{
    // Fast input/output for competitive programming.
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long numberOfTrees;
    long long requiredWood;

    cin >> numberOfTrees >> requiredWood;

    vector<long long> treeHeights(numberOfTrees);

    // Read heights of all trees.
    for (int i = 0; i < numberOfTrees; i++)
        cin >> treeHeights[i];

    Solution solver;

    cout << solver.solveEKO(treeHeights, requiredWood);

    return 0;
}
