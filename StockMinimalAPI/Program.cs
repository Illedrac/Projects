using FastEndpoints;
using FastEndpoints.Swagger;
using Microsoft.EntityFrameworkCore;
using MongoDB.Bson.Serialization;
using MongoDB.Entities;
﻿using Order = MongoDB.Entities.Order;

var bld = WebApplication.CreateBuilder();

bld.Services
   .AddSingleton(new DbContext("JobStoreDatabase", "localhost"))
   .AddFastEndpoints()
   .SwaggerDocument()
   .AddJobQueues<JobRecord, JobProvider>();

var app = bld.Build();

app.UseFastEndpoints()
   .UseHttpsRedirection()
   .UseSwaggerGen()
   .UseJobQueues();

app.Run();

#region Models



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

/// <summary>
/// A class to represent a stock
/// </summary>
/// <param name="companyName"> The name of the Company </param>
/// <param name="buyPrice"> The current sell price of the stock </param>
/// <param name="amountOfShares"> The amount of stock shares owned </param>
public record Stock(string companyName, double buyPrice, double amountOfShares);


public class BuyStockEvent
{
    public required string companyName { get; set; }
    public required double buyPrice { get; set; }
    public required double amountOfShares { get; set; }
}
#endregion

#region Commands

public class GetStockCommand : ICommand<string>
{
    public required string companyName { set; get; }
    public required double buyPrice { set; get; }
    public required double amountOfShares { set; get; }
}

public class JobQueueCommand : ICommand
{
    public int Id { get; set; }
    public string message { get; init; } = default!;
}
#endregion

#region Endpoints

/// <summary>
/// FastEndpoints: This is a POST request endpoint
/// </summary>
public class CreateStockEndpoint : Endpoint<Stock, List<Stock>>
{
    public override void Configure()
    {
        Post("/api/owned-stocks");
        AllowAnonymous();
    }

    public override async Task HandleAsync(Stock req, CancellationToken ct)
    {
        OwnedStockDB.OwnedStockData.Add(req);

        await SendAsync(OwnedStockDB.OwnedStockData, cancellation: ct);
    }
}

/// <summary>
/// FastEndpoints: This is a GET request endpoint
/// </summary>
/// Notice how this is an (Endpoint) : EndpointWithoutRequest as opposed to the endpoint above. 
/// Since there's no request, assume it's just asking for the OwnedStockDB List
public class GetStockEndpoint : EndpointWithoutRequest<List<Stock>>
{
    public override void Configure()
    {
        Get("/api/owned-stocks");
        AllowAnonymous();
    }

    public override async Task HandleAsync(CancellationToken ct)
    {
        await SendAsync(OwnedStockDB.OwnedStockData, cancellation: ct);
    }
}

/// <summary>
/// FastEndpoints: This is a GET request endpoint
/// </summary>
/// Again, notice how this is an EndpointWithoutRequest
/// The endpoint (since it includes the companyName string in the url) will use that given company name to return the stock data
public class GetStockByCompanyNameEndpoint : EndpointWithoutRequest<Stock>
{
    public override void Configure()
    {
        Get("/api/owned-stocks/{companyName}");
        AllowAnonymous();
    }

    public override async Task HandleAsync(CancellationToken ct)
    {
        var companyNameFromRoute = Route<string>("companyName");
        var stock = OwnedStockDB.OwnedStockData.FirstOrDefault(x => x.companyName == companyNameFromRoute);

        if (stock is null)
        {
            await SendNotFoundAsync(cancellation: ct);
            return;
        }

        await SendAsync(stock, cancellation: ct);
    }
}

/// <summary>
/// FastEndpoints: This is a PUT request endpoint
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

        if(stockIndex == -1)
        {
            await SendNotFoundAsync(cancellation: ct);
            return;
        }

        OwnedStockDB.OwnedStockData[stockIndex] = req;

        await SendAsync(OwnedStockDB.OwnedStockData[stockIndex]);

        
    }
}


/// <summary>
/// FastEndpoints: This is a DELETE request endpoint
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

public class BuyStockEndpoint : Endpoint<Stock>
{
    public override void Configure()
    {
        Post("/api/owned-stocks/buy");
        AllowAnonymous();
    }

    public override async Task HandleAsync(Stock req, CancellationToken ct)
    {
        await PublishAsync(new BuyStockEvent
        {
            companyName = req.companyName,
            amountOfShares = req.amountOfShares,
            buyPrice = req.buyPrice
        });

        await SendOkAsync(cancellation: ct);
    }
}

public class GetFullStockInformation : EndpointWithoutRequest<string>
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

            var stockInformation = await new GetStockCommand()
            {
                companyName = OwnedStockDB.OwnedStockData[stockIndex].companyName,
                buyPrice = OwnedStockDB.OwnedStockData[stockIndex].buyPrice,
                amountOfShares = OwnedStockDB.OwnedStockData[stockIndex].amountOfShares

            }.ExecuteAsync();
            
            await SendAsync(stockInformation);
        }
    }


sealed class SayHelloEndpoint : EndpointWithoutRequest
{
    public override void Configure()
    {
        Post("/api/job-queue-command");
        AllowAnonymous();
    }
    public override async Task HandleAsync(CancellationToken c)
    {
        for (var i = 1; i <= 10; i++)
        {
            await new JobQueueCommand
            {
                Id = i,
                message = "JobQueueCommand"
            }.QueueJobAsync(ct: c);
        }
        await SendAsync("all jobs queued!", cancellation: c);
    }
}
#endregion

#region EventHandler

public class StockBoughtHandler : IEventHandler<BuyStockEvent>
{
    private readonly ILogger _logger;

    public StockBoughtHandler(ILogger<StockBoughtHandler> logger)
    {
        _logger = logger;
    }

    public Task HandleAsync(BuyStockEvent eventModel, CancellationToken ct)
    {
        // Not sure where to view this information
        _logger.LogInformation($"Stock Bought Event Recieved: [{eventModel.companyName}]");
        return Task.CompletedTask;
    }
}

public class GetStockHandler : ICommandHandler<GetStockCommand, string>
{
    public Task<string> ExecuteAsync(GetStockCommand command, CancellationToken ct)
    {
        var result = "You own " + command.amountOfShares + " share(s) of "
                     + command.companyName + " bought at $" + command.buyPrice;

        return Task.FromResult(result);
    }
}

public class JobQueueCommandHandler(ILogger<JobQueueCommand> logger) : ICommandHandler<JobQueueCommand>
{
    public async Task ExecuteAsync(JobQueueCommand command, CancellationToken ct)
    {
        await Task.Delay(5, ct);

        logger.LogInformation(" JobQueueCommand from id : {id} message {msg}", command.Id, command.message);

    }
}

#endregion

#region JobQueue

public sealed class JobRecord : Entity, IJobStorageRecord
{
    public string QueueID { get; set; } = default!;
    public object Command { get; set; } = default!;
    public DateTime ExecuteAfter { get; set; }
    public DateTime ExpireOn { get; set; }
    public bool IsComplete { get; set; }
}

sealed class JobProvider(DbContext db, ILogger<JobProvider> logger) : IJobStorageProvider<JobRecord>
{
    public Task StoreJobAsync(JobRecord job, CancellationToken ct)
        => db.SaveAsync(job, ct);

    public async Task<IEnumerable<JobRecord>> GetNextBatchAsync(PendingJobSearchParams<JobRecord> p)
        => await db.Find<JobRecord>()
                   .Match(p.Match)
                   .Sort(r => r.ID, Order.Ascending)
                   .Limit(p.Limit)
                   .ExecuteAsync(p.CancellationToken);

    public Task MarkJobAsCompleteAsync(JobRecord job, CancellationToken ct)
        => db.Update<JobRecord>()
             .MatchID(job.ID)
             .Modify(r => r.IsComplete, true)
             .ExecuteAsync(ct);

    public Task OnHandlerExecutionFailureAsync(JobRecord job, Exception exception, CancellationToken ct)
    {
        logger.LogInformation("Rescheduling failed job to be retried after 60 seconds...");

        return db.Update<JobRecord>()
                 .MatchID(job.ID)
                 .Modify(r => r.ExecuteAfter, DateTime.UtcNow.AddMinutes(1))
                 .ExecuteAsync(ct);
    }

    public Task PurgeStaleJobsAsync(StaleJobSearchParams<JobRecord> p)
        => db.DeleteAsync(p.Match, p.CancellationToken);
}

sealed class DbContext : DBContext
{
    public DbContext(string database, string host) : base(database, host)
    {
        var objectSerializer = new MongoDB.Bson.Serialization.Serializers.ObjectSerializer(type =>
            MongoDB.Bson.Serialization.Serializers.ObjectSerializer.DefaultAllowedTypes(type) ||
            type.FullName!.EndsWith("Command"));

        BsonSerializer.RegisterSerializer(objectSerializer);
    }
}
#endregion