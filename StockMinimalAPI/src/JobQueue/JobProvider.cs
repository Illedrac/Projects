using FastEndpoints;
using System.Runtime.ConstrainedExecution;

sealed class JobProvider(ILogger<JobProvider> logger) : IJobStorageProvider<JobRecord>
{
    List<JobRecord> jobs = [];
    public async Task StoreJobAsync(JobRecord job, CancellationToken ct)
    {
        await Task.Run(() => { jobs.Add(job); }, ct);

        Console.WriteLine("STOREJOBASYNC. Jobs.Count(): " + jobs.Count());
    }
    public async Task<IEnumerable<JobRecord>> GetNextBatchAsync(PendingJobSearchParams<JobRecord> p)
    {
        Console.WriteLine("GETNEXTBATCHASYNC");
        return jobs;
    }
    // I know this is not async but it'll do for now
    public async Task MarkJobAsCompleteAsync(JobRecord job, CancellationToken ct)
    {
        Console.WriteLine("MARKJOBASCOMPLETE");

        var index = 0;
        while(index < jobs.Count())  
        {
            if (jobs[index].QueueID == job.QueueID)
                jobs.Remove(jobs[index]);
            else
                index++;
        }

        await Task.CompletedTask; 
    
    }

    public Task OnHandlerExecutionFailureAsync(JobRecord job, Exception exception, CancellationToken ct)
    {
        Console.WriteLine("ONHANDLEREXECUTIONFAILURE");

        logger.LogInformation("Rescheduling failed job to be retried after 60 seconds...");

        jobs.Find(match: q => q.QueueID == job.QueueID).ExecuteAfter = DateTime.Now.AddMinutes(1);

        return Task.CompletedTask;
    }

    public Task PurgeStaleJobsAsync(StaleJobSearchParams<JobRecord> p)
    {
        Console.WriteLine("PURGESTALEJOBS");

        foreach (JobRecord cur in jobs.FindAll(q => q.Equals(p)))
        {
            jobs.Remove(cur);

        }

        return Task.CompletedTask;
    }
    
}
