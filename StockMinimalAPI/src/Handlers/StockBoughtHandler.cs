using FastEndpoints;

/// <summary>
/// This is an event handler for the StockBought event
/// It simply logs to the logger that there was a StockBoughtEvent received with the company name of the Stock DTO
/// </summary>
public class StockBoughtHandler : IEventHandler<Stock>
{
    private readonly ILogger _logger;

    public StockBoughtHandler(ILogger<StockBoughtHandler> logger)
    {
        _logger = logger;
    }

    public Task HandleAsync(Stock eventModel, CancellationToken ct)
    {
        // Not sure where to view this information
        _logger.LogInformation($"Stock Bought Event Recieved: [{eventModel.companyName}]");
        return Task.CompletedTask;
    }
}