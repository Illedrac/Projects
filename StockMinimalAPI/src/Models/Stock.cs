/// <summary>
/// A class to represent a stock
/// </summary>
/// <param name="companyName"> The name of the Company </param>
/// <param name="buyPrice"> The current sell price of the stock </param>
/// <param name="amountOfShares"> The amount of stock shares owned </param>
public record Stock(string companyName, double buyPrice, double amountOfShares);
