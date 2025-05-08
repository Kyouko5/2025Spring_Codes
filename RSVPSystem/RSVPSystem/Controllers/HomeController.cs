using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using RSVPSystem.Data;
using RSVPSystem.Models;
using System.Diagnostics;

namespace RSVPSystem.Controllers
{
    public class HomeController : Controller
    {
        private readonly ApplicationDbContext _context;

        public HomeController(ApplicationDbContext context)
        {
            _context = context;
        }

        public async Task<IActionResult> Index()
        {
            // Display list of parties
            return View(await _context.Parties.ToListAsync());
        }

        // Display registration page
        [HttpGet]
        public IActionResult Register(int partyId)
        {
            ViewBag.Party = _context.Parties.FirstOrDefault(p => p.Id == partyId);
            return View();
        }

        // Process registration submission
        [HttpPost]
        public async Task<IActionResult> Register(Attendee attendee, int partyId)
        {
            if (ModelState.IsValid)
            {
                // Check if attendee already exists
                var existingAttendee = await _context.Attendees
                    .FirstOrDefaultAsync(a => a.Email == attendee.Email);

                if (existingAttendee == null)
                {
                    // Add new attendee
                    _context.Attendees.Add(attendee);
                    await _context.SaveChangesAsync();
                    existingAttendee = attendee;
                }

                // Check if already registered for this party
                var alreadyRegistered = await _context.Set<AttendeeParty>()
                    .AnyAsync(ap => ap.AttendeeId == existingAttendee.Id && ap.PartyId == partyId);

                if (!alreadyRegistered)
                {
                    // Create relationship between attendee and party
                    var attendeeParty = new AttendeeParty
                    {
                        AttendeeId = existingAttendee.Id,
                        PartyId = partyId
                    };
                    
                    _context.Add(attendeeParty);
                    await _context.SaveChangesAsync();
                }

                return RedirectToAction("ShowAttendees", new { partyId });
            }

            ViewBag.Party = _context.Parties.FirstOrDefault(p => p.Id == partyId);
            return View(attendee);
        }

        // Show attendee information
        public async Task<IActionResult> ShowAttendees(int partyId)
        {
            var party = await _context.Parties.FindAsync(partyId);
            
            if (party == null)
            {
                return NotFound();
            }

            var attendees = await _context.Attendees
                .Where(a => a.AttendeeParties.Any(ap => ap.PartyId == partyId))
                .ToListAsync();
                
            ViewBag.PartyName = party.Name;
            return View(attendees);
        }

        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }
    }
}