
using FastEndpoints;

public class GetStockHandler : ICommandHandler<GetStockCommand, string>
{
    public Task<string> ExecuteAsync(GetStockCommand command, CancellationToken ct)
    {
        var result = "You own " + command.amountOfShares + " share(s) of "
                     + command.companyName + " bought at $" + command.buyPrice;

        return Task.FromResult(result);
    }
}
