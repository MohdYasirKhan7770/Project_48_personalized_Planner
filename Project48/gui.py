"""
Personalized Learning Path & Assessment Planner — GUI
======================================================
A Python/Tkinter front-end that mirrors the C console program.
All the same DAA algorithms are implemented here:
  - Linear Search (Search Topic)
  - Threshold Filtering (Detect Weak Topics)
  - Selection Sort with Urgency formula (Rank Topics)
  - Adjacency Matrix graph (Prerequisites)
"""

import tkinter as tk
from tkinter import ttk, messagebox, simpledialog

# ── Constants ────────────────────────────────────────────────────────────────
MAX_TOPICS = 100

# ── Data Storage (mirrors the C struct arrays) ───────────────────────────────
topics = []          # list of dicts: {id, name, difficulty, priority, studyHours, score}
adj = [[0] * MAX_TOPICS for _ in range(MAX_TOPICS)]   # adjacency matrix


# ══════════════════════════════════════════════════════════════════════════════
#  ALGORITHM HELPERS  (same logic as your C code)
# ══════════════════════════════════════════════════════════════════════════════

def get_index_by_id(topic_id):
    """Linear Search — O(n) — find array index for a given topic ID."""
    for i, t in enumerate(topics):
        if t["id"] == topic_id:
            return i
    return -1


def calculate_urgency(t):
    """Urgency = (Priority * 20) + (100 - Score)"""
    return t["priority"] * 20.0 + (100.0 - t["score"])


def selection_sort_descending(arr):
    """Selection Sort — O(n²) — sort a list copy by urgency (descending)."""
    n = len(arr)
    for i in range(n - 1):
        max_idx = i
        for j in range(i + 1, n):
            if calculate_urgency(arr[j]) > calculate_urgency(arr[max_idx]):
                max_idx = j
        if max_idx != i:
            arr[i], arr[max_idx] = arr[max_idx], arr[i]
    return arr


# ══════════════════════════════════════════════════════════════════════════════
#  GUI APPLICATION
# ══════════════════════════════════════════════════════════════════════════════

class PlannerApp(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("Personalized Learning Path Planner")
        self.geometry("900x620")
        self.configure(bg="#1e1e2e")
        self.resizable(False, False)

        self._build_header()
        self._build_sidebar()
        self._build_main_area()

    # ── Header ───────────────────────────────────────────────────────────────
    def _build_header(self):
        header = tk.Frame(self, bg="#313244", height=56)
        header.pack(fill="x")
        header.pack_propagate(False)
        tk.Label(
            header,
            text="📚  Personalized Learning Path Planner",
            font=("Segoe UI", 16, "bold"),
            fg="#cdd6f4", bg="#313244",
        ).pack(side="left", padx=16)
        tk.Label(
            header,
            text=f"Topics: {len(topics)}",
            font=("Segoe UI", 11),
            fg="#a6adc8", bg="#313244",
            name="topic_counter",
        ).pack(side="right", padx=16)

    # ── Sidebar with menu buttons ────────────────────────────────────────────
    def _build_sidebar(self):
        sidebar = tk.Frame(self, bg="#181825", width=220)
        sidebar.pack(side="left", fill="y")
        sidebar.pack_propagate(False)

        tk.Label(
            sidebar, text="MENU", font=("Segoe UI", 10, "bold"),
            fg="#6c7086", bg="#181825",
        ).pack(pady=(18, 6))

        buttons = [
            ("➕  Add Topic",                self.add_topic),
            ("📋  View All Topics",          self.view_topics),
            ("🔍  Search Topic",             self.search_topic),
            ("⚠️  Detect Weak Topics",       self.detect_weak),
            ("📊  Rank by Urgency",          self.rank_topics),
            ("🔗  Add Prerequisite",         self.add_prerequisite),
            ("🗺️  View Prerequisites",       self.view_prerequisites),
        ]
        for text, cmd in buttons:
            btn = tk.Button(
                sidebar, text=text, command=cmd,
                font=("Segoe UI", 11), anchor="w",
                fg="#cdd6f4", bg="#313244",
                activebackground="#45475a", activeforeground="#cdd6f4",
                bd=0, padx=14, pady=8, cursor="hand2",
            )
            btn.pack(fill="x", padx=10, pady=3)

    # ── Main output area ─────────────────────────────────────────────────────
    def _build_main_area(self):
        main = tk.Frame(self, bg="#1e1e2e")
        main.pack(side="left", fill="both", expand=True)

        self.output = tk.Text(
            main, wrap="word",
            font=("Consolas", 11),
            fg="#cdd6f4", bg="#1e1e2e",
            insertbackground="#cdd6f4",
            selectbackground="#45475a",
            bd=0, padx=16, pady=16,
            state="disabled",
        )
        scrollbar = ttk.Scrollbar(main, command=self.output.yview)
        self.output.configure(yscrollcommand=scrollbar.set)
        scrollbar.pack(side="right", fill="y")
        self.output.pack(fill="both", expand=True)

        self._print_welcome()

    # ── Helper: write to output panel ────────────────────────────────────────
    def _out(self, text):
        self.output.configure(state="normal")
        self.output.insert("end", text + "\n")
        self.output.see("end")
        self.output.configure(state="disabled")

    def _clear(self):
        self.output.configure(state="normal")
        self.output.delete("1.0", "end")
        self.output.configure(state="disabled")

    def _update_counter(self):
        # Update the topic counter in the header
        for widget in self.winfo_children():
            if isinstance(widget, tk.Frame):
                for child in widget.winfo_children():
                    if str(child).endswith("topic_counter"):
                        child.configure(text=f"Topics: {len(topics)}")
                        return

    def _print_welcome(self):
        self._out("========================================")
        self._out("  Welcome to the Learning Path Planner!")
        self._out("========================================")
        self._out("")
        self._out("  Use the menu on the left to get started.")
        self._out("  Start by adding some topics (➕ Add Topic).")
        self._out("")

    # ══════════════════════════════════════════════════════════════════════════
    #  FEATURE 1 — Add Topic
    # ══════════════════════════════════════════════════════════════════════════
    def add_topic(self):
        if len(topics) >= MAX_TOPICS:
            messagebox.showwarning("Limit", "Maximum 100 topics reached!")
            return

        win = tk.Toplevel(self)
        win.title("Add New Topic")
        win.geometry("360x380")
        win.configure(bg="#1e1e2e")
        win.resizable(False, False)
        win.grab_set()

        fields = {}
        labels = [
            ("Topic ID:", "id"),
            ("Topic Name:", "name"),
            ("Difficulty (1-5):", "difficulty"),
            ("Priority (1-5):", "priority"),
            ("Study Hours:", "studyHours"),
            ("Assessment Score (%):", "score"),
        ]
        for i, (label_text, key) in enumerate(labels):
            tk.Label(
                win, text=label_text,
                font=("Segoe UI", 10), fg="#cdd6f4", bg="#1e1e2e",
            ).grid(row=i, column=0, padx=14, pady=6, sticky="w")
            entry = tk.Entry(
                win, font=("Segoe UI", 10),
                fg="#cdd6f4", bg="#313244",
                insertbackground="#cdd6f4", bd=0,
            )
            entry.grid(row=i, column=1, padx=14, pady=6, sticky="ew")
            fields[key] = entry
        win.columnconfigure(1, weight=1)

        def save():
            try:
                tid = int(fields["id"].get())
                name = fields["name"].get().strip()
                diff = int(fields["difficulty"].get())
                pri = int(fields["priority"].get())
                hrs = int(fields["studyHours"].get())
                score = float(fields["score"].get())
            except ValueError:
                messagebox.showerror("Input Error", "Please enter valid values.\n\n"
                    "ID, Difficulty, Priority, Study Hours must be integers.\n"
                    "Score must be a number.", parent=win)
                return

            if not name:
                messagebox.showerror("Input Error", "Topic name cannot be empty.", parent=win)
                return
            if not (1 <= diff <= 5) or not (1 <= pri <= 5):
                messagebox.showerror("Input Error", "Difficulty and Priority must be 1-5.", parent=win)
                return
            if hrs < 0:
                messagebox.showerror("Input Error", "Study Hours cannot be negative.", parent=win)
                return
            if get_index_by_id(tid) != -1:
                messagebox.showerror("Input Error", f"Topic ID {tid} already exists!", parent=win)
                return

            topics.append({
                "id": tid, "name": name, "difficulty": diff,
                "priority": pri, "studyHours": hrs, "score": score,
            })
            self._update_counter()
            self._out(f"✅ Topic added: [{tid}] {name}  "
                      f"(Diff:{diff} Pri:{pri} Hrs:{hrs} Score:{score}%)")
            win.destroy()

        tk.Button(
            win, text="Save Topic", command=save,
            font=("Segoe UI", 11, "bold"),
            fg="#1e1e2e", bg="#a6e3a1",
            activebackground="#94e2d5", bd=0,
            padx=20, pady=8, cursor="hand2",
        ).grid(row=len(labels), column=0, columnspan=2, pady=18)

    # ══════════════════════════════════════════════════════════════════════════
    #  FEATURE 2 — View All Topics
    # ══════════════════════════════════════════════════════════════════════════
    def view_topics(self):
        self._clear()
        if not topics:
            self._out("No topics have been added yet.")
            return

        self._out("═══════════════════ ALL TOPICS ═══════════════════")
        self._out(f"{'ID':<6} {'Name':<20} {'Diff':<6} {'Pri':<6} {'Hrs':<6} {'Score':<8}")
        self._out("─" * 56)
        for t in topics:
            self._out(f"{t['id']:<6} {t['name']:<20} {t['difficulty']:<6} "
                      f"{t['priority']:<6} {t['studyHours']:<6} {t['score']:.2f}%")
        self._out("─" * 56)
        self._out(f"Total topics: {len(topics)}")

    # ══════════════════════════════════════════════════════════════════════════
    #  FEATURE 3 — Search Topic (Linear Search)
    # ══════════════════════════════════════════════════════════════════════════
    def search_topic(self):
        if not topics:
            messagebox.showinfo("Info", "No topics added yet.")
            return
        raw = simpledialog.askstring("Search", "Enter Topic ID to search:", parent=self)
        if raw is None:
            return
        try:
            search_id = int(raw)
        except ValueError:
            messagebox.showerror("Error", "Please enter a valid integer ID.")
            return

        self._clear()
        idx = get_index_by_id(search_id)
        if idx == -1:
            self._out(f"❌ Topic with ID {search_id} not found!")
        else:
            t = topics[idx]
            self._out("────────── Topic Found ──────────")
            self._out(f"  ID:         {t['id']}")
            self._out(f"  Name:       {t['name']}")
            self._out(f"  Difficulty: {t['difficulty']}")
            self._out(f"  Priority:   {t['priority']}")
            self._out(f"  Study Hrs:  {t['studyHours']}")
            self._out(f"  Score:      {t['score']:.2f}%")
            self._out("─────────────────────────────────")

    # ══════════════════════════════════════════════════════════════════════════
    #  FEATURE 4 — Detect Weak Topics (Threshold Filtering)
    # ══════════════════════════════════════════════════════════════════════════
    def detect_weak(self):
        if not topics:
            messagebox.showinfo("Info", "No topics added yet.")
            return
        raw = simpledialog.askstring(
            "Weak Topics", "Enter weakness threshold (e.g. 50):", parent=self)
        if raw is None:
            return
        try:
            threshold = float(raw)
        except ValueError:
            messagebox.showerror("Error", "Please enter a valid number.")
            return

        self._clear()
        self._out(f"══════ WEAK TOPICS (Score < {threshold:.1f}%) ══════")
        weak = [t for t in topics if t["score"] < threshold]
        if not weak:
            self._out("\n✅ Great! No weak topics found.")
        else:
            for t in weak:
                self._out(f"\n  ⚠️  {t['name']} (ID {t['id']})")
                self._out(f"      Score: {t['score']:.2f}%")
                self._out(f"      Difficulty: {t['difficulty']}  |  Priority: {t['priority']}")
            self._out(f"\n──────────────────────────────")
            self._out(f"Total weak topics: {len(weak)} out of {len(topics)}")

    # ══════════════════════════════════════════════════════════════════════════
    #  FEATURE 5 — Rank Topics (Selection Sort by Urgency)
    # ══════════════════════════════════════════════════════════════════════════
    def rank_topics(self):
        if not topics:
            messagebox.showinfo("Info", "No topics added yet.")
            return

        self._clear()
        sorted_topics = selection_sort_descending(list(topics))  # sort a copy

        self._out("═══════════════════════════════════════════════════════")
        self._out("  RANKED TOPICS (Most Urgent → Least Urgent)")
        self._out("  Formula: Urgency = (Priority × 20) + (100 − Score)")
        self._out("═══════════════════════════════════════════════════════")
        self._out(f"{'Rank':<6} {'ID':<6} {'Name':<20} {'Pri':<6} {'Score':<10} {'Urgency':<10}")
        self._out("─" * 60)
        for i, t in enumerate(sorted_topics):
            urg = calculate_urgency(t)
            self._out(f"{i+1:<6} {t['id']:<6} {t['name']:<20} "
                      f"{t['priority']:<6} {t['score']:>6.2f}%   {urg:>8.2f}")
        self._out("─" * 60)

    # ══════════════════════════════════════════════════════════════════════════
    #  FEATURE 6 — Add Prerequisite (Adjacency Matrix)
    # ══════════════════════════════════════════════════════════════════════════
    def add_prerequisite(self):
        if len(topics) < 2:
            messagebox.showinfo("Info", "You need at least 2 topics first.")
            return

        win = tk.Toplevel(self)
        win.title("Add Prerequisite")
        win.geometry("380x200")
        win.configure(bg="#1e1e2e")
        win.resizable(False, False)
        win.grab_set()

        tk.Label(win, text="[Prerequisite] must be studied BEFORE [Target]",
                 font=("Segoe UI", 10, "italic"), fg="#a6adc8", bg="#1e1e2e"
                 ).grid(row=0, column=0, columnspan=2, padx=14, pady=(14, 6))

        tk.Label(win, text="Prerequisite Topic ID:", font=("Segoe UI", 10),
                 fg="#cdd6f4", bg="#1e1e2e").grid(row=1, column=0, padx=14, pady=6, sticky="w")
        prereq_entry = tk.Entry(win, font=("Segoe UI", 10), fg="#cdd6f4",
                                bg="#313244", insertbackground="#cdd6f4", bd=0)
        prereq_entry.grid(row=1, column=1, padx=14, pady=6, sticky="ew")

        tk.Label(win, text="Target Topic ID:", font=("Segoe UI", 10),
                 fg="#cdd6f4", bg="#1e1e2e").grid(row=2, column=0, padx=14, pady=6, sticky="w")
        target_entry = tk.Entry(win, font=("Segoe UI", 10), fg="#cdd6f4",
                                bg="#313244", insertbackground="#cdd6f4", bd=0)
        target_entry.grid(row=2, column=1, padx=14, pady=6, sticky="ew")
        win.columnconfigure(1, weight=1)

        def save():
            try:
                prereq_id = int(prereq_entry.get())
                target_id = int(target_entry.get())
            except ValueError:
                messagebox.showerror("Error", "Enter valid integer IDs.", parent=win)
                return
            if prereq_id == target_id:
                messagebox.showerror("Error", "A topic cannot be its own prerequisite!", parent=win)
                return
            u = get_index_by_id(prereq_id)
            v = get_index_by_id(target_id)
            if u == -1:
                messagebox.showerror("Error", f"Prerequisite ID {prereq_id} not found!", parent=win)
                return
            if v == -1:
                messagebox.showerror("Error", f"Target ID {target_id} not found!", parent=win)
                return
            if adj[u][v] == 1:
                messagebox.showinfo("Info", "This relationship already exists!", parent=win)
                return

            adj[u][v] = 1
            self._out(f"🔗 Prerequisite added: '{topics[u]['name']}' (ID {prereq_id})"
                      f"  →  '{topics[v]['name']}' (ID {target_id})")
            win.destroy()

        tk.Button(
            win, text="Add Prerequisite", command=save,
            font=("Segoe UI", 11, "bold"),
            fg="#1e1e2e", bg="#89b4fa",
            activebackground="#74c7ec", bd=0,
            padx=20, pady=8, cursor="hand2",
        ).grid(row=3, column=0, columnspan=2, pady=18)

    # ══════════════════════════════════════════════════════════════════════════
    #  FEATURE 7 — View Prerequisites (Graph Display)
    # ══════════════════════════════════════════════════════════════════════════
    def view_prerequisites(self):
        self._clear()
        if not topics:
            self._out("No topics added yet.")
            return

        self._out("═══════════════════════════════════════════════════")
        self._out("        PREREQUISITE RELATIONSHIPS (GRAPH)")
        self._out("═══════════════════════════════════════════════════")
        count = 0
        n = len(topics)
        for i in range(n):
            for j in range(n):
                if adj[i][j] == 1:
                    self._out(f"  [{topics[i]['id']}] {topics[i]['name']:<18}"
                              f"  ───►  [{topics[j]['id']}] {topics[j]['name']}")
                    count += 1
        if count == 0:
            self._out("  No prerequisite relationships defined yet.")
        else:
            self._out("───────────────────────────────────────────────────")
            self._out(f"  Total prerequisite rules: {count}")


# ══════════════════════════════════════════════════════════════════════════════
#  LAUNCH
# ══════════════════════════════════════════════════════════════════════════════
if __name__ == "__main__":
    app = PlannerApp()
    app.mainloop()
