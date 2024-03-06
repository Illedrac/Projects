/// <summary>
/// A "Database" class to hold "owned" Stocks
/// </summary>
public static class OwnedStockDB
{
    /// <summary>
    /// The main "database" of owned stocks 
    /// </summary>
    public static readonly List<Stock> OwnedStockData =
    [
        new("VeeFriends", 999.99, 999.99),
        new("Meta", 498.19, 10),
        new("Lockheed Martin", 431.94, 1)
    ];
}