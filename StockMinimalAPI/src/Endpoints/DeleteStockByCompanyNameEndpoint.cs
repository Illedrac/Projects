using FastEndpoints;

/// <summary>
/// FastEndpoints: This is a DELETE request endpoint
/// Given the companyName in the url, it will delete that Stock DTO from the DB
/// </summary>
public class DeleteStockByCompanyNameEndpoint : EndpointWithoutRequest<List<Stock>>
{
    public override void Configure()
    {
        // This 
        Delete("/api/owned-stocks/{companyName}");
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

        OwnedStockDB.OwnedStockData.RemoveAt(stockIndex);

        await SendAsync(OwnedStockDB.OwnedStockData);


    }
}