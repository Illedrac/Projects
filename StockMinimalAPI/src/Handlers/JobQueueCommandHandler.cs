using FastEndpoints;

/// <summary>
/// This is a command handler for the JobQueueCommand
/// It simply logs to the logger that there was a JobQueueCommand received with the id and message from the JobQueueCommand
/// </summary>
public class JobQueueCommandHandler(ILogger<JobQueueCommand> logger) : ICommandHandler<JobQueueCommand>
{
    public async Task ExecuteAsync(JobQueueCommand command, CancellationToken ct)
    {
        await Task.Delay(1, ct);

        logger.LogInformation(" JobQueueCommand from id : {id} message {msg}", command.Id, command.message);

    }
}