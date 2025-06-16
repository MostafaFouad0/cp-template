vector<vector<array<int, 3>>> queries(SQT + 1);
for (int i = 0, l, r; i < q; i++)
    {
	    // take queries
        cin >> l >> r;
        l--, r--;
        if (r - l + 1 > SQT)
            queries[l / SQT].push_back({r, l, i});
        else
        {
	        /* 
		        brute force logic here
	        */
	        // rollback here
            for (int j = l; j <= r; j++)
            {
                int val = a[j];
                first[val] = last[val] = -1;
            }
            // save the answer
            ansq[i] = tmp_ans;
        }
    }
    for (int i = 0; i < SQT; i++)
    {
        if (queries[i].empty())continue;
        sort(queries[i].begin(), queries[i].end());
        memset(first, -1, sizeof(first));
        memset(last, -1, sizeof(last));
        // end at the last element in this bucket
        int r = (i + 1) * SQT - 2, ans{};
				// only add, there is no remove 
        for (const auto& [rq,lq,iq] : queries[i])
        {
            while (r < rq)
            {
                int val = a[++r];
                if (first[val] != -1)
                {
                    last[val] = r;
                    ans = max(ans, last[val] - first[val]);
                }
                else
                {
                    first[val] = last[val] = r;
                }
            }
            vector<array<int, 3>> updates;
            int l = (i + 1) * SQT - 1, tmp = ans;
            while (l > lq)
            {
                int val = a[--l];
                updates.push_back({val, first[val], last[val]});
                if (first[val] != -1)
                {
                    first[val] = l;
                    tmp = max(tmp, last[val] - first[val]);
                }
                else
                {
                    first[val] = last[val] = l;
                }
            }
            /// rollback
            reverse(updates.begin(), updates.end());
            for (auto& [val,f,l] : updates)
            {
                first[val] = f;
                last[val] = l;
            }
            ansq[iq] = tmp;
        }
    }
    for (auto& it : ansq)cout << it << "\n";
