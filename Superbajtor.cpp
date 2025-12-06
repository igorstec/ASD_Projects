#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Segment {
    char c;
    long long len;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    cin >> Q;

    vector<Segment> segments;

    for (int q = 0; q < Q; q++) {
        long long pos, k;
        char c;
        cin >> pos >> k >> c;

        if (segments.empty()) {
            segments.push_back({c, k});
        } else {
            // Find the segment containing position pos
            long long cumPos = 0;
            int idx = 0;

            while (idx < segments.size() && cumPos + segments[idx].len <= pos) {
                cumPos += segments[idx].len;
                idx++;
            }

            if (idx == segments.size()) {
                // Insert at the end
                if (segments.back().c == c) {
                    segments.back().len += k;
                } else {
                    segments.push_back({c, k});
                }
            } else {
                // Insert within or at the start of segment idx
                long long offsetInSegment = pos - cumPos;

                if (offsetInSegment == 0) {
                    // At the boundary before segment idx
                    bool mergePrev = (idx > 0 && segments[idx - 1].c == c);
                    bool mergeCurr = (segments[idx].c == c);

                    if (mergePrev && mergeCurr) {
                        // Merge all three
                        segments[idx - 1].len += k + segments[idx].len;
                        segments.erase(segments.begin() + idx);
                    } else if (mergePrev) {
                        // Merge with previous
                        segments[idx - 1].len += k;
                    } else if (mergeCurr) {
                        // Merge with current
                        segments[idx].len += k;
                    } else {
                        // Insert as new segment
                        segments.insert(segments.begin() + idx, {c, k});
                    }
                } else {
                    // In the middle of segment idx
                    if (segments[idx].c == c) {
                        // Same character, just add
                        segments[idx].len += k;
                    } else {
                        // Split the segment
                        long long leftLen = offsetInSegment;
                        long long rightLen = segments[idx].len - offsetInSegment;
                        char segChar = segments[idx].c;

                        segments[idx].len = leftLen;
                        segments.insert(segments.begin() + idx + 1, {c, k});
                        segments.insert(segments.begin() + idx + 2, {segChar, rightLen});
                    }
                }
            }
        }

	    // Find the maximum segment length
        long long maxLen = 0;
        for (const auto& seg : segments) {
            maxLen = max(maxLen, seg.len);
        }

        cout << maxLen << "\n";
    }

    return 0;
}
