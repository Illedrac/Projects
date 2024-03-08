
using FastEndpoints;

/// <summary>
/// This is a command handler for the GetStockCommand
/// It returns a "toString" of the GetStockCommand
/// </summary>
public class GetStockInfoHandler : ICommandHandler<GetStockInfoCommand, string>
{
    public Task<string> ExecuteAsync(GetStockInfoCommand command, CancellationToken ct)
    {
        var result = "You own " + command.amountOfShares + " share(s) of "
                     + command.companyName + " bought at $" + command.buyPrice;

        return Task.FromResult(result);
    }
}
