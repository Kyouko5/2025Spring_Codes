using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using RSVPSystem.Data;
using RSVPSystem.Models;

namespace RSVPSystem.Controllers
{
    public class RSVPController : Controller
    {
        private readonly ApplicationDbContext _context;

        public RSVPController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: RSVP
        public async Task<IActionResult> Index()
        {
            var rsvps = await _context.Attendees
                .Include(a => a.AttendeeParties)
                .ThenInclude(ap => ap.Party)
                .ToListAsync();

            return View(rsvps);
        }

        // GET: RSVP/Create
        public async Task<IActionResult> Create()
        {
            ViewData["AttendeeId"] = new SelectList(await _context.Attendees.ToListAsync(), "Id", "Name");
            ViewData["PartyId"] = new SelectList(await _context.Parties.ToListAsync(), "Id", "Name");
            
            return View();
        }

        // POST: RSVP/Create
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create(int attendeeId, int partyId)
        {
            // Check if the RSVP already exists
            var existingRsvp = await _context.Set<AttendeeParty>()
                .FirstOrDefaultAsync(ap => ap.AttendeeId == attendeeId && ap.PartyId == partyId);

            if (existingRsvp != null)
            {
                ModelState.AddModelError(string.Empty, "This person is already registered for this party.");
                ViewData["AttendeeId"] = new SelectList(await _context.Attendees.ToListAsync(), "Id", "Name", attendeeId);
                ViewData["PartyId"] = new SelectList(await _context.Parties.ToListAsync(), "Id", "Name", partyId);
                return View();
            }

            if (ModelState.IsValid)
            {
                var rsvp = new AttendeeParty
                {
                    AttendeeId = attendeeId,
                    PartyId = partyId
                };

                _context.Add(rsvp);
                await _context.SaveChangesAsync();
                return RedirectToAction(nameof(Index));
            }

            ViewData["AttendeeId"] = new SelectList(await _context.Attendees.ToListAsync(), "Id", "Name", attendeeId);
            ViewData["PartyId"] = new SelectList(await _context.Parties.ToListAsync(), "Id", "Name", partyId);
            return View();
        }

        // GET: RSVP/Delete
        public async Task<IActionResult> Delete(int? attendeeId, int? partyId)
        {
            if (attendeeId == null || partyId == null)
            {
                return NotFound();
            }

            var rsvp = await _context.Set<AttendeeParty>()
                .Include(ap => ap.Attendee)
                .Include(ap => ap.Party)
                .FirstOrDefaultAsync(ap => ap.AttendeeId == attendeeId && ap.PartyId == partyId);

            if (rsvp == null)
            {
                return NotFound();
            }

            return View(rsvp);
        }

        // POST: RSVP/Delete
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteConfirmed(int attendeeId, int partyId)
        {
            var rsvp = await _context.Set<AttendeeParty>()
                .FirstOrDefaultAsync(ap => ap.AttendeeId == attendeeId && ap.PartyId == partyId);

            if (rsvp != null)
            {
                _context.Remove(rsvp);
                await _context.SaveChangesAsync();
            }

            return RedirectToAction(nameof(Index));
        }
    }
} 