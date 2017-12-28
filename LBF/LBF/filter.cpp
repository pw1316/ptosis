#include "filter.h"

#include <stdio.h>
#include <vector>

using std::string;
using std::vector;

void pw::filterExp1Point5(const vector<double>& in, vector<double>& out)
{
    size_t N = in.size();
    out.resize(N);
    if (N < 5)
    {
        for (int i = 0; i < N; i++)
        {
            out[i] = in[i];
        }
    }
    else
    {
        out[0] = (3.0f * in[0] + 2.0f * in[1] + in[2] - in[4]) / 5.0f;
        out[1] = (4.0f * in[0] + 3.0f * in[1] + 2.0f * in[2] + in[3]) / 10.0f;
        for (int i = 2; i < N - 2; i++)
        {
            out[i] = (in[i - 2] + in[i - 1] + in[i] + in[i + 1] + in[i + 2]) / 5.0f;
        }
        out[N - 2] = (4.0f * in[N - 1] + 3.0f * in[N - 2] + 2.0f * in[N - 3] + in[N - 4]) / 10.0f;
        out[N - 1] = (3.0f * in[N - 1] + 2.0f * in[N - 2] + in[N - 3] - in[N - 5]) / 5.0f;
    }
}

void pw::filterExp2Point5(const vector<double>& in, vector<double>& out)
{
    size_t N = in.size();
    out.resize(N);
    if (N < 5)
    {
        for (int i = 0; i < N; i++)
        {
            out[i] = in[i];
        }
    }
    else
    {
        out[0] = (31.0f * in[0] + 9.0f * in[1] - 3.0f * in[2] - 5.0f * in[3] + 3.0f * in[4]) / 35.0f;
        out[1] = (9.0f * in[0] + 13.0f * in[1] + 12.0f * in[2] + 6.0f * in[3] - 5.0f * in[4]) / 35.0f;
        for (int i = 2; i < N - 2; i++)
        {
            out[i] = (-3.0f * (in[i - 2] + in[i + 2]) + 12.0f * (in[i - 1] + in[i + 1]) + 17.0f * in[i]) / 35.0f;
        }
        out[N - 2] = (9.0f * in[N - 1] + 13.0f * in[N - 2] + 12.0f * in[N - 3] + 6.0f * in[N - 4] - 5.0f * in[N - 5]) / 35.0f;
        out[N - 1] = (31.0f * in[N - 1] + 9.0f * in[N - 2] - 3.0f * in[N - 3] - 5.0f * in[N - 4] + 3.0f * in[N - 5]) / 35.0f;
    }
}

void pw::filter(string fname)
{
    fname = fname.substr(0Ui64, fname.find_last_of('.'));
    FILE* fp = NULL;
    int frame;
    float left_eye, right_eye;
    vector<double> left_eyes;
    vector<double> right_eyes;
    fopen_s(&fp, (fname + ".csv").c_str(), "r");
    while (fscanf(fp, "F%d, %f, %f\n", &frame, &left_eye, &right_eye) > 0)
    {
        left_eyes.push_back(left_eye);
        right_eyes.push_back(right_eye);
    }
    fclose(fp);
    vector<double> left_out;
    vector<double> right_out;
    filterExp1Point5(left_eyes, left_out);
    filterExp1Point5(right_eyes, right_out);

    fopen_s(&fp, (fname + "_filtered.csv").c_str(), "w");
    for (size_t i = 0; i < left_out.size(); i++)
    {
        fprintf(fp, "F%04zu, %2.4f, %2.4f\n", i, left_out[i], right_out[i]);
    }
    fclose(fp);
}
