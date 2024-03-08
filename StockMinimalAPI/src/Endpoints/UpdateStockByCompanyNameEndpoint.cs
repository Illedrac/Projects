using FastEndpoints;

/// <summary>
/// FastEndpoints: This is a PUT request endpoint
/// Given a Stock DTO request, this allows you to update a Stock DTO in the DB matching on companyName
/// </summary>
public class UpdateStockByCompanyNameEndpoint : Endpoint<Stock, Stock>
{
    public override void Configure()
    {
        // This 
        Put("/api/owned-stocks/");
        AllowAnonymous();
    }

    public override async Task HandleAsync(Stock req, CancellationToken ct)
    {
        int stockIndex = -1;

        for (int i = 0; i < OwnedStockDB.OwnedStockData.Count(); i++)
        {
            if (String.Equals(OwnedStockDB.OwnedStockData[i].companyName, req.companyName))
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

        OwnedStockDB.OwnedStockData[stockIndex] = req;

        await SendAsync(OwnedStockDB.OwnedStockData[stockIndex]);


    }
}

