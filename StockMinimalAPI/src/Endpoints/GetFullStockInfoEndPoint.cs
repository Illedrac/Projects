using FastEndpoints;

/// <summary>
/// FastEndpoints: This is a GET request endpoint
/// Given a companyName in the URL, this creates a new GetStockCommand which will then be executed
/// </summary>
public class GetFullStockInfoEndPoint : EndpointWithoutRequest<string>
{
    public override void Configure()
    {
        Get("/api/owned-stocks/full-info/{companyName}");
        AllowAnonymous();
    }

    public override async Task HandleAsync(CancellationToken ct)
    {
        int stockIndex = -1;
        var companyNameFromRoute = Route<string>("companyName");

        for (int i = 0; i < OwnedStockDB.OwnedStockData.Count(); i++)
        {
            if (String.Equals(OwnedStockDB.OwnedStockData[i].companyName, companyNameFromRoute))
            {
                stockIndex = i;
                break;
            }
        }

        if (stockIndex == -1)
        {
            await SendNotFoundAsync(cancellation: ct);
            return;
        }

        var stockInformation = await new GetStockInfoCommand()
        {
            companyName = OwnedStockDB.OwnedStockData[stockIndex].companyName,
            buyPrice = OwnedStockDB.OwnedStockData[stockIndex].buyPrice,
            amountOfShares = OwnedStockDB.OwnedStockData[stockIndex].amountOfShares

        }.ExecuteAsync();

        await SendAsync(stockInformation);
    }
}

