# Grafici-GFX agent guide

Use the repository-local skill that fits the task:

| Task | Skill |
| --- | --- |
| Change or review internals, examples or documentation | [grafici-contribute](.agents/skills/grafici-contribute/SKILL.md) |
| Write a sketch, explain the API or diagnose an Arduino problem | [grafici-arduino](.agents/skills/grafici-arduino/SKILL.md) |

[README.md](README.md) covers usage. [CONTRIBUTE.md](CONTRIBUTE.md) is the maintained reference for architecture, ownership, boundary contracts, memory costs and documentation style. Read the sections relevant to the change.

Keep patches focused and preserve C++11 support. Sources, plotters and windows meet through normalized interfaces; pixel conversion belongs at the display boundary. Host tests, rendering tools and generated pictures belong in [Grafici-Test](https://github.com/cattanimarco/Grafici-Test), outside the Arduino library.

Be concise and direct. Avoid generic filler and unnecessary rewrites. Explain measured results separately from estimates.
