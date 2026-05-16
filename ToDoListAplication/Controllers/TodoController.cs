using Microsoft.AspNetCore.Mvc;
using ToDoListAplication.Models;
using System.Collections.Generic;
using System.Linq;

namespace ToDoListAplication.Controllers
{
    public class TodoController : Controller
    {
        private static List<ToDoItem> _toDoItems = new List<ToDoItem>
        {
            new ToDoItem { Id = 1, Title = "Buy groceries", IsCompleted = false},
            new ToDoItem { Id = 2, Title = "Walk the dog", IsCompleted = true }
        };

        public IActionResult Index()
        {
            return View(_toDoItems);
        }

        [HttpPost]
        public IActionResult Create(string title)
        {
            if (!string.IsNullOrWhiteSpace(title))
            {
                var newItem = new ToDoItem
                {
                    Id = _toDoItems.Count + 1,
                    Title = title,
                    IsCompleted = false
                };
                _toDoItems.Add(newItem);
            }
            return RedirectToAction("Index");
        }

        [HttpPost]
        public IActionResult ToggleComplete(int id)
        {
            var item = _toDoItems.FirstOrDefault(t => t.Id == id);
            if (item != null)
            {
                item.IsCompleted = !item.IsCompleted;
            }
            return RedirectToAction(nameof(Index));
        }

        [HttpPost]
        public IActionResult Delete(int id)
        {
            var item = _toDoItems.FirstOrDefault(t => t.Id == id);
            if (item != null)
            {
                _toDoItems.Remove(item);
            }
            return RedirectToAction(nameof(Index));
        }
    }
}
