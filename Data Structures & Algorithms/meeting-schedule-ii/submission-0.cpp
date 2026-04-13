/**
 * Definition of Interval:
 * class Interval {
 * public:
 *     int start, end;
 *     Interval(int start, int end) {
 *         this->start = start;
 *         this->end = end;
 *     }
 * }
 */

class Solution {
public:
    int minMeetingRooms(vector<Interval>& intervals) {
        vector<pair<int,int>> arr;
        for(int i=0;i<intervals.size();i++){
            int alpha = (intervals[i]).start;
            int beta = (intervals[i]).end;
            arr.push_back({alpha,beta});
        }
        sort(arr.begin(),arr.end());
        int ans = 0;
        int currRooms = 0;
        multiset<int> timelines;
        for(int i=0;i<arr.size();i++){
            int stTime = arr[i].first;
            int sub = 0;
            while(timelines.size() >0 && (*timelines.begin()) <= stTime){
                sub++;
                timelines.erase(timelines.begin());
            }
            currRooms-= sub;
            currRooms++;
            timelines.insert(arr[i].second);
            ans = max(ans, currRooms);
        }
        return ans;
    }
};
