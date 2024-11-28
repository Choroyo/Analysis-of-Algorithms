import sys
class Profit:
    def __init__(self, max_profit, min_price, max_price):  # Fixing the __init__ method
        self.max_profit = max_profit
        self.min = min_price  # Renamed for clarity
        self.max = max_price  # Renamed for clarity


class StockAnalyzer:
    def max_profit_dc(self, prices, left, right):
        if left == right:
            return Profit(0, prices[left], prices[right])

        mid = left + ((right - left) >> 1)

        left_profit = self.max_profit_dc(prices, left, mid)
        right_profit = self.max_profit_dc(prices, mid + 1, right)
        maxp_among_both = max(left_profit.max_profit, right_profit.max_profit,
                              right_profit.max - left_profit.min)
        return Profit(maxp_among_both, min(left_profit.min, right_profit.min),
                      max(left_profit.max, right_profit.max))

    def maxProfit(self, prices):
        if not prices:
            return 0
        max_p = self.max_profit_dc(prices, 0, len(prices) - 1)
        return max_p.max_profit

# Check if the input file is provided as an argument
if len(sys.argv) < 2:
    print("No input file provided.")
    sys.exit(1)

# Assign the argument (input file) to a variable
input_file = sys.argv[1]

# Open the file in read mode
with open(input_file, 'r') as file:
    # Initialize an empty list
    lines = []

    # Loop through each line in the file
    for line in file:
        # Append the line to the list, stripping any extra newline characters
        lines.append(float(line.strip()))  # Convert lines to float

analyzer = StockAnalyzer()

# Calculate the maximum profit
max_profit = analyzer.maxProfit(lines)
print("The optimal solution for " + input_file + " is " + str(max_profit))
