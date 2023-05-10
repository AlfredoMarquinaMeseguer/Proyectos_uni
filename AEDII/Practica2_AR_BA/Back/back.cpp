#include <bits/stdc++.h>
using namespace std;
 
// function that tries every possible solution by calling itself recursively
void backtracking(int* arr, int n, bool* curr_elements, int no_of_selected_elements,
             bool* soln, int* min_diff, int sum, int curr_sum, int curr_position)
{
    // checks whether the it is going out of bound
    if (curr_position == n)
        return;
 
    // checks that the numbers of elements left are not less than the
    // number of elements required to form the solution
    if ((n/2 - no_of_selected_elements) > (n - curr_position))
        return;
 
    // consider the cases when current element is not included in the solution
    backtracking(arr, n, curr_elements, no_of_selected_elements,
              soln, min_diff, sum, curr_sum, curr_position+1);
 
    // add the current element to the solution
    no_of_selected_elements++;
    curr_sum = curr_sum + arr[curr_position];
    curr_elements[curr_position] = true;
 
    // checks if a solution is formed
    if (no_of_selected_elements == n/2)
    {
        // checks if the solution formed is better than the best solution so far
        if (abs(sum/2 - curr_sum) < *min_diff)
        {
            *min_diff = abs(sum/2 - curr_sum);
            for (int i = 0; i<n; i++)
                soln[i] = curr_elements[i];
        }
    }
    else
    {
        // consider the cases where current element is included in the solution
        backtracking(arr, n, curr_elements, no_of_selected_elements, soln,
                  min_diff, sum, curr_sum, curr_position+1);
    }
 
    // removes current element before returning to the caller of this function
    curr_elements[curr_position] = false;
}
 
// main function that generate an arr
void tugOfWar(int *arr, int n)
{
    // the boolean array that contains the inclusion and exclusion of an element
    // in current set. The number excluded automatically form the other set
    bool* curr_elements = new bool[n];
 
    // The inclusion/exclusion array for final solution
    bool* soln = new bool[n];
 
    int min_diff = INT_MAX;
 
    int sum = 0;
    for (int i=0; i<n; i++)
    {
        sum += arr[i];
        curr_elements[i] =  false;
        soln[i] = false;        
    }
 
    // Find the solution using recursive function backtracking()
    backtracking(arr, n, curr_elements, 0, soln, &min_diff, sum, 0, 0);
 
    int total1, total2 = 0;
    for (int i=0; i<n; i++)
    {
        if (soln[i] == true){
            total1 +=  arr[i];     
        }else{
            total2 +=  arr[i];
        }            
    }    

    if (total1 < total2) cout << total1 << " " << total2 << endl;
    else                 cout << total2 << " " << total1 << endl;    
}
 
// Driver program to test above functions
int main()
{
    int problemas, numCandidatos, candidatoActual, pesoA, pesoB;
    // int arr[] = {23, 45, -34, 12, 0, 98, -99, 4, 189, -1, 4};
    // int n = sizeof(arr)/sizeof(arr[0]);
    // tugOfWar(arr, n);
    // Entrada
    cin >> problemas;    
    // cin.getline();
    // getline(aux, cin);
    for(int i =0; i<problemas; ++i) {
        cin >> numCandidatos;
        int * candidatos = new int [numCandidatos];
        for(int j=0; j< numCandidatos; ++j) {            
            cin >> candidatoActual;
            candidatos[j] = candidatoActual;
        }
        // getline(aux, cin);
        // Fin Entrada
        // n = (numCandidatos/2) + (numCandidatos%2);
        tugOfWar(candidatos, numCandidatos);


        auto solucion = nullptr;
        if (solucion == nullptr) {
            // No debería ocurrir nunca
            // cout << "" << endl;
        } else {
            // cout << "Equipo A: ";
            // pesoA = 0;
            // for (const int &elem : solucion->equipoA) {
            //     // cout << elem << " ";
            //     pesoA += elem;
            // }
            // // cout << endl << "Equipo B: ";
            // pesoB = 0;
            // for (const int &elem : solucion->equipoB) {
            //     // cout << elem << " ";
            //     pesoB += elem;
            // }
            // // cout << endl << "Diferencia: " << diferencia(*solucion) << endl;

            // if (pesoA < pesoB) 
            //     cout << pesoA << " " << pesoB << endl;
            // else
            //     cout << pesoB << " " << pesoA << endl;
            
        }          
        // delete &equipos;
        delete candidatos;
    }   
    return 0;
}