int manacher(string s)
{
    string str;
    str += "*#";
    for (auto ch : s)
    {
        str.push_back(ch);
        str.push_back('#');
    }
    str += "#)";
    int n = str.length() - 1;
    vector<int> p((int)str.length());
    int maxid = 1, id = 1, ans = 0;
    for (int i = 1; i < n; i++)
    {
        if (i < maxid)
            p[i] = min(maxid - i, p[2 * id - i]);
        else
            p[i] = 1;
        while (str[i - p[i]] == str[i + p[i]])
            p[i]++;
        if (maxid < i + p[i])
        {
            maxid = i + p[i];
            id = i;
        }
        ans = max(ans, p[i] - 1);
    }
    return ans;
}