﻿using FastEndpoints;

/// <summary>
/// FastEndpoints: This is a POST request endpoint
/// Allows you to queue up (i) generic JobQueueCommands
/// </summary>
sealed class JobQueueEndpoint : EndpointWithoutRequest
{
    public override void Configure()
    {
        Post("/api/job-queue");
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