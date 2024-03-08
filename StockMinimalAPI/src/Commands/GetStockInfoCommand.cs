using FastEndpoints;

public class GetStockInfoCommand : ICommand<string>
{
    public required string companyName { set; get; }
    public required double buyPrice { set; get; }
    public required double amountOfShares { set; get; }
}